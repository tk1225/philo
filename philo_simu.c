/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:08:15 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/13 20:17:55 by takuokam         ###   ########.fr       */
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
		share_data->last_meal_time = \
		get_now_time(share_data->table_data->start_time);
		print_timestamp(share_data->table_data->start_time, \
		share_data->philo_id, TAKEN_FORK, \
		&share_data->table_data->action_mutex);
		print_timestamp(share_data->table_data->start_time, \
		share_data->philo_id, EATING, &share_data->table_data->action_mutex);
		share_data->status = EATING;
		share_data->eat_count ++;
		sleep_on_time(share_data->table_data->time_to_eat);
	}
	if (share_data->status == EATING)
	{
		left_fork->status = AVAILABLE;
		right_fork->status = AVAILABLE;
		print_timestamp(share_data->table_data->start_time, \
		share_data->philo_id, SLEEPING, &share_data->table_data->action_mutex);
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
	while (1)
	{
		philo_action(share_data, left_fork, right_fork);
		if (share_data->status == SLEEPING)
			sleep_on_time(share_data->table_data->time_to_sleep);
		print_timestamp(share_data->table_data->start_time, \
		share_data->philo_id, THINKING, &share_data->table_data->action_mutex);
	}
	return (p);
}