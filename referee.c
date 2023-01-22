/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   referee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:38:00 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/22 19:42:56 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		while (i < data[0]->table_data->num_philosophers)
		{
			pthread_mutex_lock(&data[0]->table_data->action_mutex);
			if ((data[i]->table_data->max_eat_count != 0) && \
			(data[i]->eat_count >= data[i]->table_data->max_eat_count))
			{
				data[0]->table_data->all_living = FALSE;
				break ;
			}
			if ((ms - data[i]->last_meal_time) > \
			data[0]->table_data->time_to_die)
			{
				print_timestamp(data[0], i + 1, DIED, data[i]->table_data);
				data[0]->table_data->all_living = FALSE;
				// printf("lastmeal%lld", data[i]->last_meal_time);
				// printf("ms%d", ms);
				break ;
			}
			pthread_mutex_unlock(&data[0]->table_data->action_mutex);
			i++;
		}
	}
	return (p);
}
