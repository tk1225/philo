/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/11 18:15:06 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_timestamp(struct timeval start_time, int philo_id, int status)
{
	char *message;
	int		ms;
	struct timeval now;

	gettimeofday(&now, NULL);
	message = "";
	if (status == TAKEN_FORK)
		message = "has taken a fork";
	else if (status == EATING)
		message = "is eating";
	else if (status == SLEEPING)
		message = "is sleeping";
	else if (status == THINKING)
		message = "is thinking";
	else if (status == DIED)
		message = "died";
	else if (status == 55)
		message = "55";
	ms = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
	// ms =  (start_time.tv_sec) * 1000 + (start_time.tv_usec) / 1000;
	// ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;

	// (void)start_time;
	// (void)now;
	printf("%d_in_ms %d %s\n", ms, philo_id, message);
}

size_t	get_mili_sec(void)
{
	struct timeval	now;
	size_t		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;

	return (ms);
}

// void sleep_on_time (size_t sleep_time_ms)
// {
// 	size_t ms;
// 	struct timeval now;

// 	gettimeofday(&now, NULL);
// 	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
// 	while((get_mili_sec() < ms + sleep_time_ms))
// 		usleep(100);
// }

void *philosophers(void *p)
{
	t_philo *share_data;

	share_data = p;

	print_timestamp(share_data->table_data->start_time, share_data->philo_id, 55);

	return (p);
}

int main(int argc, char *argv[])
{
	
	pthread_t pthread;
	t_philo *share_data;

	gettimeofday(&share_data->table_data->start_time, NULL);
	int i = 0;
	while (i < 100)
	{
		pthread_create(&pthread, NULL, &philosophers, share_data);
		i++;
	}
	pthread_join(pthread, NULL);

	return (0);
}