/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/13 19:55:45 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
