/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2022/12/20 00:56:17 by takumasaoka      ###   ########.fr       */
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
	int *left_fork;
	int *right_fork;

	share_data = p;
	left_fork = &(share_data->fork[share_data->philo_id]);
	right_fork = &(share_data->fork[(share_data->philo_id + 1) % share_data->num_philosophers]);

	// if (share_data->philo_id == share_data->num_philosophers - 1)
	// 	right_fork = &(share_data->fork[0]);
	// else
	// 	right_fork = &(share_data->fork[share_data->philo_id + 1]);

	//mutexをlistごとに分ける。
	
	//哲学者の行動
	// fork がないとき　-> あくまでthinking -> 構造体に哲学者のステータスを持たせthinkingなら毎回出力しない。
	// あるときは-> 奇数は左が先、　偶数は右を先にとる。両方INUSEに変更し、eating/sleeping
	// -> 
	
	while (1)
	{
		if (*left_fork == INUSE || *right_fork == INUSE)
		{
			gettimeofday(&now, NULL);
			print_timestamp(share_data->start_time, share_data->philo_id, THINKING);
			sleep_on_time(10);
		}
		//mutex_lockで待機している場合ここに入らない
		
		if (*left_fork == AVAILABLE && *right_fork == AVAILABLE)
		{
			pthread_mutex_lock(share_data->mutex);
			*left_fork = INUSE;
			*right_fork = INUSE;
			print_timestamp(share_data->start_time, share_data->philo_id, TAKEN_FORK);
			print_timestamp(share_data->start_time, share_data->philo_id, EATING);
			pthread_mutex_unlock(share_data->mutex);
			//eating time
			sleep_on_time(share_data->time_to_eat);
			// usleep(share_data->time_to_eat * 1000);
			pthread_mutex_lock(share_data->mutex);
			*left_fork = AVAILABLE;
			*right_fork = AVAILABLE;
			pthread_mutex_unlock(share_data->mutex);
			print_timestamp(share_data->start_time, share_data->philo_id, SLEEPING);
			sleep_on_time(share_data->time_to_sleep);
		}
		

		

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
		
		pthread_create(&pthread, NULL, &philosophers, tmp);
		num_philosophers--;
	}
	free(share_data);
  	pthread_join(pthread, NULL);
}

int main(int argc, char *argv[])
{
	
	pthread_mutex_t mutex;
	t_philo *share_data;
	int		num_philosophers;
	int *fork_list;

	if (argc <= 1)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	pthread_mutex_init(&mutex, NULL);
	num_philosophers = ft_atoi(argv[1]);
	fork_list = (int *)ft_calloc(num_philosophers, sizeof(int));

	share_data->time_to_die = ft_atoi(argv[2]);
	share_data->time_to_eat = ft_atoi(argv[3]);
	share_data->time_to_sleep = ft_atoi(argv[4]);
	share_data->mutex = &mutex;
	share_data->fork = fork_list;
	share_data->num_philosophers = num_philosophers;
	share_data->someone_is_dead = FALSE;
	create_thread(share_data, num_philosophers);

	// int i = 0;
	// while (share_data->num_philosophers --)
	// {
	// 	printf("fork%d\n", share_data->fork[i]);
	// 	i ++;
	// }	

	return (0);
}