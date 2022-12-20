/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2022/12/20 16:46:09 by takuokam         ###   ########.fr       */
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
	// left_fork = &(share_data->fork[share_data->philo_id]);
	// right_fork = &(share_data->fork[(share_data->philo_id + 1) % share_data->num_philosophers]);

	left_fork = (share_data->mutex_fork[share_data->philo_id]);
	right_fork = (share_data->mutex_fork[(share_data->philo_id + 1) % share_data->num_philosophers]);
	//mutexをlistごとに分ける。
	//哲学者の行動
	// fork がないとき　-> あくまでthinking -> 構造体に哲学者のステータスを持たせthinkingなら毎回出力しない。
	// あるときは-> 奇数は左が先、　偶数は右を先にとる。両方INUSEに変更し、eating/sleeping
	// ->
	
	while (1)
	{
		// pthread_mutex_lock(share_data->mutex);
		pthread_mutex_lock(left_fork->mutex);
		pthread_mutex_lock(right_fork->mutex);
		if (left_fork->status == INUSE || right_fork->status == INUSE)
		{
			gettimeofday(&now, NULL);
			if (share_data->status != THINKING)
			{
				share_data->status = THINKING;
				print_timestamp(share_data->start_time, share_data->philo_id, THINKING);
			}
			// sleep_on_time(10);
		}
		pthread_mutex_unlock(left_fork->mutex);
		pthread_mutex_unlock(right_fork->mutex);
		// pthread_mutex_unlock(share_data->mutex);

		//mutex_lockで待機している場合ここに入らない
		// pthread_mutex_lock(share_data->mutex);
		pthread_mutex_lock(left_fork->mutex);
		pthread_mutex_lock(right_fork->mutex);
		if (left_fork->status == AVAILABLE && right_fork->status == AVAILABLE)
		{
			left_fork->status = INUSE;
			right_fork->status = INUSE;
			print_timestamp(share_data->start_time, share_data->philo_id, TAKEN_FORK);
			print_timestamp(share_data->start_time, share_data->philo_id, EATING);
			share_data->status = EATING;
		}
		// pthread_mutex_unlock(share_data->mutex);
		pthread_mutex_unlock(left_fork->mutex);
		pthread_mutex_unlock(right_fork->mutex);
		//eating time
		if (share_data->status == EATING)
			sleep_on_time(share_data->time_to_eat);

		// pthread_mutex_lock(share_data->mutex);
		pthread_mutex_lock(left_fork->mutex);
		pthread_mutex_lock(right_fork->mutex);
		if (left_fork->status == INUSE && right_fork->status == INUSE && share_data->status == EATING)
		{
				
			left_fork->status = AVAILABLE;
			right_fork->status = AVAILABLE;
				
			print_timestamp(share_data->start_time, share_data->philo_id, SLEEPING);
			share_data->status = SLEEPING;
		}
		// pthread_mutex_unlock(share_data->mutex);
		pthread_mutex_unlock(left_fork->mutex);
		pthread_mutex_unlock(right_fork->mutex);
			
		if (share_data->status == SLEEPING)
			sleep_on_time(share_data->time_to_sleep);
	}
	// usleep(share_data->time_to_sleep * 1000);

	// int i = 0;
	// printf("philo%d\n", share_data->num_philosophers);

	// while (i < share_data->num_philosophers)
	// {
	// 	printf("fork%d\n", share_data->fork[i]);
	// 	i ++;
	// }

	return (p);
}

t_philo *share_data_copy(t_philo *share_data)
{
	t_philo *res;
	
	res = (t_philo *)malloc(sizeof(t_philo));
	res->fork = share_data->fork;
	res->mutex = share_data->mutex;
	res->philo_id = share_data->philo_id;
	res->time_to_die = share_data->time_to_die;
	res->time_to_eat = share_data->time_to_eat;
	res->time_to_sleep = share_data->time_to_sleep;
	res->num_philosophers = share_data->num_philosophers;
	res->start_time = share_data->start_time;
	res->mutex_fork = share_data->mutex_fork;

	return (res);
}

void create_thread(t_philo *share_data, int num_philosophers)
{
	pthread_t pthread;
	t_philo *tmp;

	gettimeofday(&share_data->start_time, NULL);
	while (num_philosophers)
	{
		tmp = share_data_copy(share_data);
		tmp->philo_id = num_philosophers - 1;
		tmp->status = THINKING;
		pthread_create(&pthread, NULL, &philosophers, tmp);
		num_philosophers--;
	}
	free(share_data);
  	pthread_join(pthread, NULL);
}

static void each_fork_init(t_fork 	**fork_struct_list, int i)
{
	t_fork *each_fork;
	pthread_mutex_t each_mutex;

	each_fork = (t_fork *)malloc(sizeof(t_fork));
	pthread_mutex_init(&each_mutex, NULL);
	each_fork->mutex = &each_mutex;
	each_fork->status = AVAILABLE;
	fork_struct_list[i] = each_fork;
}

int main(int argc, char *argv[])
{
	
	pthread_mutex_t mutex;
	t_philo *share_data;
	int		num_philosophers;
	int *fork_list;
	t_fork 	**fork_struct_list;

	if (argc <= 1)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	pthread_mutex_init(&mutex, NULL);
	num_philosophers = ft_atoi(argv[1]);
	fork_list = (int *)ft_calloc(num_philosophers, sizeof(int));

	//fork_init
	fork_struct_list = (t_fork **)malloc(sizeof(t_fork*) * num_philosophers);

	int i;

	i = 0;
	while (i < num_philosophers)
	{
		each_fork_init(fork_struct_list, i);
		i ++;
	}
	

	share_data->time_to_die = ft_atoi(argv[2]);
	share_data->time_to_eat = ft_atoi(argv[3]);
	share_data->time_to_sleep = ft_atoi(argv[4]);
	share_data->mutex = &mutex;
	share_data->fork = fork_list;
	share_data->num_philosophers = num_philosophers;
	share_data->someone_is_dead = FALSE;
	share_data->mutex_fork = fork_struct_list;
	create_thread(share_data, num_philosophers);

	// int i = 0;
	// while (share_data->num_philosophers --)
	// {
	// 	printf("fork%d\n", share_data->fork[i]);
	// 	i ++;
	// }	

	return (0);
}