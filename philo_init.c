/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2022/12/16 17:14:56 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosophers(void *p)
{
	t_philo *share_data;
	struct timeval tv;
	int *left_fork;
	int *right_fork;

	share_data = p;
	pthread_mutex_lock(share_data->mutex);
	left_fork = &(share_data->fork[share_data->philo_id]);
	if (share_data->philo_id == share_data->num_philosophers - 1)
		right_fork = &(share_data->fork[0]);
	else
		right_fork = &(share_data->fork[share_data->philo_id + 1]);
	
	if (*left_fork == INUSE || *right_fork == INUSE)
	{
		gettimeofday(&tv, NULL);
		print_timestamp(tv, share_data->philo_id, THINKING);
		while (*left_fork == INUSE || *right_fork == INUSE)
		{
		}
	}
	if (*left_fork == AVAILABLE && *right_fork == AVAILABLE)
	{
		*left_fork = INUSE;
		*right_fork = INUSE;
		gettimeofday(&tv, NULL);
		print_timestamp(tv, share_data->philo_id, TAKEN_FORK);
		print_timestamp(tv, share_data->philo_id, EATING);
		usleep(100000);
		*left_fork = AVAILABLE;
		*right_fork = AVAILABLE;
	}
	pthread_mutex_unlock(share_data->mutex);
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

	return (res);
}

void create_thread(t_philo *share_data, int num_philosophers)
{
	pthread_t pthread;
	t_philo *tmp;

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

	// mutex = NULL;
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
	
	create_thread(share_data, num_philosophers);

	// int i = 0;
	// while (share_data->num_philosophers --)
	// {
	// 	printf("fork%d\n", share_data->fork[i]);
	// 	i ++;
	// }	

	return (0);
}