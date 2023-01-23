/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   referee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:38:00 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/23 19:13:09 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	referee_helper(t_philo	**data, int i, int ms)
{
	while (i < data[0]->table_data->num_philosophers)
	{
		pthread_mutex_lock(&data[0]->table_data->action_mutex);
		if ((data[i]->table_data->max_eat_count != 0) && \
		(data[i]->eat_count >= data[i]->table_data->max_eat_count))
		{
			data[0]->table_data->all_living = FALSE;
			pthread_mutex_unlock(&data[0]->table_data->action_mutex);
			break ;
		}
		if ((ms - data[i]->last_meal_time) > data[0]->table_data->time_to_die)
		{
			print_die(data[0], i + 1, data[i]->table_data);
			data[0]->table_data->all_living = FALSE;
			pthread_mutex_unlock(&data[0]->table_data->action_mutex);
			break ;
		}
		pthread_mutex_unlock(&data[0]->table_data->action_mutex);
		i++;
	}
}

void	*referee(void *p)
{
	t_philo	**data;
	int		i;
	int		ms;

	data = p;
	while (data[0]->table_data->all_living)
	{
		i = 0;
		ms = get_now_time(data[i]->table_data->start_time);
		referee_helper(data, i, ms);
	}
	return (p);
}
