/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   referee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:38:00 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/13 20:02:37 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *referee(void *p)
{
	t_philo **data;
	data = p;

	while (1)
	{
		int i;
		int ms;

		i = 0;
		ms = get_now_time(data[i]->table_data->start_time);
		while (i < data[0]->table_data->num_philosophers)
		{	
			if ((data[i]->table_data->max_eat_count != 0) && (data[i]->eat_count >= data[i]->table_data->max_eat_count))
				exit(1);
			if ((ms - data[i]->last_meal_time) > data[0]->table_data->time_to_die )
			{
				print_timestamp(data[i]->table_data->start_time, i + 1, DIED, &data[i]->table_data->action_mutex);
				// printf("ms%d\n", ms);
				// printf("lastmealtime%lld", data[i]->last_meal_time);
				exit(0);
			}
			i++;
		}
	}
	return (p);
}