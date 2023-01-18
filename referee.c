/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   referee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:38:00 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/18 20:07:59 by takumasaoka      ###   ########.fr       */
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
		// usleep(10);
		i = 0;
		ms = get_now_time(data[i]->table_data->start_time);
		while (i < data[0]->table_data->num_philosophers)
		{
			if ((data[i]->table_data->max_eat_count != 0) && \
			(data[i]->eat_count >= data[i]->table_data->max_eat_count))
			{
				data[0]->table_data->all_living = FALSE;
				break ;
			}
			if ((ms - data[i]->last_meal_time) > \
			data[0]->table_data->time_to_die)
			{
				print_timestamp(data[i]->table_data->start_time, \
				i + 1, DIED, data[i]->table_data);
				data[0]->table_data->all_living = FALSE;
				printf("lastmeal%lld", data[i]->last_meal_time);
				printf("ms%d", ms);
				break ;
			}
			i++;
		}
	}
	return (p);
}
