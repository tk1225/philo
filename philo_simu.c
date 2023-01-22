/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:08:15 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/22 20:08:04 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_action(t_philo *share_data, \
t_fork *left_fork, t_fork	*right_fork)
{
	mutex_lock(&right_fork->mutex, &left_fork->mutex);
	if (left_fork->status == AVAILABLE && right_fork->status == AVAILABLE)
	{
		left_fork->status = INUSE;
		right_fork->status = INUSE;
		print_timestamp(share_data, \
		share_data->philo_id, TAKEN_FORK, \
		share_data->table_data);
		print_timestamp(share_data, \
		share_data->philo_id, EATING, share_data->table_data);
		share_data->status = EATING;
		sleep_on_time(share_data->table_data->time_to_eat);
	}
	if (share_data->status == EATING)
	{
		left_fork->status = AVAILABLE;
		right_fork->status = AVAILABLE;
		print_timestamp(share_data, \
		share_data->philo_id, SLEEPING, share_data->table_data);
		share_data->status = SLEEPING;
	}
	mutex_unlock(&right_fork->mutex, &left_fork->mutex);
}

void	*philosophers(void *p)
{
	t_philo	*share_data;
	t_fork	*left_fork;
	t_fork	*right_fork;

	share_data = p;
	left_fork = (share_data->mutex_fork[share_data->philo_id - 1]);
	right_fork = (share_data->mutex_fork[(share_data->philo_id) % \
	share_data->table_data->num_philosophers]);
	if (share_data->philo_id % 2 == 0)
		usleep(15000);
	while (share_data->table_data->all_living)
	{
		philo_action(share_data, left_fork, right_fork);
		if (share_data->status == SLEEPING)
			sleep_on_time(share_data->table_data->time_to_sleep);
		print_timestamp(share_data, \
		share_data->philo_id, THINKING, share_data->table_data);
	}
	return (p);
}
