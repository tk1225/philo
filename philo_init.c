/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/11 19:09:49 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_mili_sec(void)
{
	struct timeval	now;
	size_t		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;

	return (ms);
}

void sleep_on_time (size_t sleep_time_ms)
{
	size_t ms;
	struct timeval now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	while((get_mili_sec() < ms + sleep_time_ms))
		usleep(100);
}



void *philosophers(void *p)
{
	t_philo *share_data;
	struct timeval now;
	t_fork *left_fork;
	t_fork *right_fork;
	

	share_data = p;

	// printf("%d", share_data->last_meal_time);
	// print_timestamp(share_data->table_data->start_time, share_data->philo_id, 55);

	left_fork = (share_data->mutex_fork[share_data->philo_id]);
	right_fork = (share_data->mutex_fork[(share_data->philo_id + 1) % share_data->table_data->num_philosophers]);
	
	//哲学者の行動
	// fork がないとき-> あくまでthinking -> 構造体に哲学者のステータスを持たせthinkingなら毎回出力しない。
	// あるときは-> 奇数は左が先、偶数は右を先にとる。両方INUSEに変更し、eating/sleeping
	// ->
	
	while (1)
	{
		mutex_lock(share_data, &right_fork->mutex, &left_fork->mutex);
		if (left_fork->status == INUSE || right_fork->status == INUSE)
		{
			if (share_data->status != THINKING)
			{
				share_data->status = THINKING;
				print_timestamp(share_data->table_data->start_time, share_data->philo_id, THINKING);
			}
		}
		if (left_fork->status == AVAILABLE && right_fork->status == AVAILABLE)
		{
			left_fork->status = INUSE;
			right_fork->status = INUSE;
			gettimeofday(&now, NULL);
			share_data->last_meal_time = (now.tv_sec - share_data->table_data->start_time.tv_sec) * 1000 + (now.tv_usec - share_data->table_data->start_time.tv_usec) / 1000;
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, TAKEN_FORK);
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, EATING);
			share_data->status = EATING;
		}
		mutex_unlock(&right_fork->mutex, &left_fork->mutex);

		if (share_data->status == EATING)
			sleep_on_time(share_data->table_data->time_to_eat);

		if (share_data->status == EATING)
		{
			mutex_lock(share_data, &right_fork->mutex, &left_fork->mutex);
			left_fork->status = AVAILABLE;
			right_fork->status = AVAILABLE;	
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, SLEEPING);
			share_data->status = SLEEPING;
			mutex_unlock(&right_fork->mutex, &left_fork->mutex);
		}
		if (share_data->status == SLEEPING)
			sleep_on_time(share_data->table_data->time_to_sleep);
		if (share_data->status == THINKING)
			usleep(10);
	}

	return (p);
}

void *referee(void *p)
{
	t_philo **data;
	data = p;
	// sleep_on_time(100);
	while (1)
	{
		// sleep_on_time(10);
		int i;
		struct timeval now;
		size_t ms;

		i = 0;
		gettimeofday(&now, NULL);
		ms = (now.tv_sec - data[i]->table_data->start_time.tv_sec) * 1000 + (now.tv_usec - data[i]->table_data->start_time.tv_usec) / 1000;
		// printf("%zu\n", ms);
		while (i < data[0]->table_data->num_philosophers)
		{
			// printf("num%d\n", data[0]->table_data->num_philosophers);
			// printf("lastmeal%d\n", data[i]->last_meal_time);
			
			if ((ms - data[i]->last_meal_time) > data[0]->table_data->time_to_die )
			{
				print_timestamp(data[i]->table_data->start_time, i, DIED);
				exit(0);
			}
			i++;
		}
		// print_timestamp(data[0]->table_data->start_time, data[0]->philo_id, 55);
	}
	return (p);
}

t_philo *share_data_copy(t_philo *share_data)
{
	t_philo *res;
	
	res = (t_philo *)malloc(sizeof(t_philo));
	res->philo_id = share_data->philo_id;
	res->mutex_fork = share_data->mutex_fork;
	res->table_data = share_data->table_data;

	return (res);
}

void create_thread(t_philo *share_data, int num_philosophers)
{
	pthread_t pthread;
	t_philo *tmp[200];
	int i;
	
	i = 0;

	while (i < num_philosophers)
	{
		tmp[i] = share_data_copy(share_data);
		tmp[i]->philo_id = i;
		tmp[i]->status = THINKING;
		tmp[i]->last_meal_time = 0;
		i++;
	}

	gettimeofday(&share_data->table_data->start_time, NULL);
	i = 0;
	while (i < num_philosophers)
	{
		pthread_create(&pthread, NULL, &philosophers, tmp[i]);
		i++;
	}
	pthread_create(&pthread, NULL, &referee, tmp);
	
	free(share_data);
  	pthread_join(pthread, NULL);
}

static void each_fork_init(t_fork 	**fork_struct_list, int i)
{
	t_fork *each_fork;

	each_fork = (t_fork *)malloc(sizeof(t_fork));
	pthread_mutex_init(&each_fork->mutex, NULL);
	each_fork->status = AVAILABLE;
	fork_struct_list[i] = each_fork;
}

int main(int argc, char *argv[])
{
	t_philo *share_data;
	t_fork 	**fork_struct_list;

	if (argc <= 1)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	share_data->table_data = (t_table *)malloc(sizeof(t_table));

	share_data->table_data->num_philosophers = ft_atoi(argv[1]);
	fork_struct_list = (t_fork **)malloc(sizeof(t_fork*) * share_data->table_data->num_philosophers);

	int i;

	i = 0;
	while (i < share_data->table_data->num_philosophers)
	{
		each_fork_init(fork_struct_list, i);
		i ++;
	}
	
	share_data->table_data->time_to_die = ft_atoi(argv[2]);
	share_data->table_data->time_to_eat = ft_atoi(argv[3]);
	share_data->table_data->time_to_sleep = ft_atoi(argv[4]);
	share_data->table_data->someone_is_dead = FALSE;
	share_data->mutex_fork = fork_struct_list;
	create_thread(share_data, share_data->table_data->num_philosophers);

	return (0);
}