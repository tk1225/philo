/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:17:05 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/11 18:19:10 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void mutex_lock_for_odd(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	int res;

	res = pthread_mutex_lock(right_fork);
	if (res != 0)
		return ;
	pthread_mutex_lock(left_fork);
	if (res != 0)
		return ;
}

static void mutex_lock_for_even(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	int res;

	res = pthread_mutex_lock(left_fork);
	if (res != 0)
		return ;
	res = pthread_mutex_lock(right_fork);
	if (res != 0)
		return ;
}

void mutex_lock(t_philo *share_data, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	if (share_data->philo_id % 2 == 0)
		mutex_lock_for_even(right_fork, left_fork);
	else
		mutex_lock_for_odd(right_fork, left_fork);
}

void mutex_unlock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}