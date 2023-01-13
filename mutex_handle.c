/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:17:05 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/13 20:07:40 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_lock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
}

void	mutex_unlock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}
