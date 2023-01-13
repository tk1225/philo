/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/13 17:06:08 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_fork *left_fork;
	t_fork *right_fork;

	share_data = p;
	left_fork = (share_data->mutex_fork[share_data->philo_id - 1]);
	right_fork = (share_data->mutex_fork[(share_data->philo_id) % share_data->table_data->num_philosophers]);
	if (share_data->philo_id % 2 == 0)
		usleep(15000);
	while (1)
	{
		mutex_lock(share_data, &right_fork->mutex, &left_fork->mutex);
		if (left_fork->status == AVAILABLE && right_fork->status == AVAILABLE)
		{
			left_fork->status = INUSE;
			right_fork->status = INUSE;
			share_data->last_meal_time = get_now_time(share_data->table_data->start_time);
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, TAKEN_FORK);
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, EATING);
			share_data->status = EATING;
			share_data->eat_count ++;
			sleep_on_time(share_data->table_data->time_to_eat);
		}
		if (share_data->status == EATING)
		{
			left_fork->status = AVAILABLE;
			right_fork->status = AVAILABLE;	
			print_timestamp(share_data->table_data->start_time, share_data->philo_id, SLEEPING);
			share_data->status = SLEEPING;
		}
		mutex_unlock(share_data, &right_fork->mutex, &left_fork->mutex);

		if (share_data->status == SLEEPING)
			sleep_on_time(share_data->table_data->time_to_sleep);
		print_timestamp(share_data->table_data->start_time, share_data->philo_id, THINKING);
	}
	return (p);
}

void *referee(void *p)
{
	t_philo **data;
	data = p;

	while (1)
	{
		int i;
		int ms;

		i = 0;
		ms = get_now_time(data[i]->table_data->start_time);
		while (i < data[0]->table_data->num_philosophers)
		{	
			if (data[i]->eat_count >= data[i]->table_data->max_eat_count)
				exit(1);
			if ((ms - data[i]->last_meal_time) > data[0]->table_data->time_to_die )
			{
				print_timestamp(data[i]->table_data->start_time, i + 1, DIED);
				// printf("ms%d\n", ms);
				// printf("lastmealtime%lld", data[i]->last_meal_time);
				exit(0);
			}
			i++;
		}
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
		tmp[i]->philo_id = i + 1;
		tmp[i]->status = THINKING;
		tmp[i]->last_meal_time = 0;
		tmp[i]->eat_count = 0;
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
	int i;

	if (argc <= 1 || argc <= 4)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	share_data->table_data = (t_table *)malloc(sizeof(t_table));
	share_data->table_data->num_philosophers = ft_atoi(argv[1]);
	fork_struct_list = (t_fork **)malloc(sizeof(t_fork*) * share_data->table_data->num_philosophers);

	i = 0;
	while (i < share_data->table_data->num_philosophers)
	{
		each_fork_init(fork_struct_list, i);
		i ++;
	}
	share_data->table_data->time_to_die = ft_atoi(argv[2]);
	share_data->table_data->time_to_eat = ft_atoi(argv[3]);
	share_data->table_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		share_data->table_data->max_eat_count = ft_atoi(argv[5]);
	share_data->table_data->someone_is_dead = FALSE;
	share_data->mutex_fork = fork_struct_list;
	create_thread(share_data, share_data->table_data->num_philosophers);

	return (0);
}