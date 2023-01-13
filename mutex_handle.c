/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:17:05 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/13 15:22:59 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void mutex_lock_for_odd(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork, int philo_id)
// {
// 	int err;
// 	(void) philo_id;

// 	err = pthread_mutex_lock(right_fork);
// 	printf("%dtake********right\n",philo_id);

// 	if (err != 0)
// 		return ;
// 	pthread_mutex_lock(left_fork);
// 	printf("%dtake********left\n",philo_id);

// 	if (err != 0)
// 		return ;
// }

static void mutex_lock_for_even(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork, int philo_id)
{
	int err;
	(void) philo_id;
	err = pthread_mutex_lock(left_fork);
	// printf("%dtake********left\n",philo_id);
	if (err != 0)
		return ;
	err = pthread_mutex_lock(right_fork);
	// printf("%dtake********right\n",philo_id);
	if (err != 0)
		return ;
}

void mutex_lock(t_philo *share_data, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	(void)share_data;
	// if (share_data->philo_id % 2 == 0)
		mutex_lock_for_even(right_fork, left_fork, share_data->philo_id);
	// else
	// 	mutex_lock_for_odd(right_fork, left_fork, share_data->philo_id);
}

// static void mutex_unlock_for_odd(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork, int philo_id)
// {
// 	int err;
// 	(void) philo_id;
// 	err = pthread_mutex_unlock(right_fork);
// 	// printf("%dtake********right\n",philo_id);
// 	if (err != 0)
// 		return ;
// 	pthread_mutex_unlock(left_fork);
// 	// printf("%dtake********left\n",philo_id);
// 	if (err != 0)
// 		return ;
// }
// static void mutex_unlock_for_even(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork, int philo_id)
// {
// 	int err;
// 	(void) philo_id;
// 	err = pthread_mutex_unlock(left_fork);
// 	// printf("%dtake********left\n",philo_id);
// 	if (err != 0)
// 		return ;
// 	err = pthread_mutex_unlock(right_fork);
// 	// printf("%dtake********right\n",philo_id);
// 	if (err != 0)
// 		return ;
// }

void mutex_unlock(t_philo *share_data, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	(void)share_data;
	// if (share_data->philo_id % 2 == 0)
	// 	mutex_unlock_for_odd(right_fork, left_fork, share_data->philo_id);
	// else
	// 	mutex_unlock_for_even(right_fork, left_fork, share_data->philo_id);
	pthread_mutex_unlock(left_fork);
	// printf("%dput********left\n",share_data->philo_id);
	pthread_mutex_unlock(right_fork);
	// printf("%dput********right\n",share_data->philo_id);

}