/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:08:35 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/23 19:12:44 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_timestamp(t_philo *share_data, \
	int philo_id, int status, t_table	*table_data)
{
	char	*message;
	int		now;

	pthread_mutex_lock(&table_data->action_mutex);
	if (table_data->all_living == FALSE)
	{
		pthread_mutex_unlock(&table_data->action_mutex);
		return ;
	}
		// return ;
	message = "";
	now = get_now_time(share_data->table_data->start_time);
	if (status == TAKEN_FORK)
		message = "has taken a fork";
	else if (status == EATING)
	{
		message = "\x1b[31mis eating\x1b[39m";
		share_data->last_meal_time = now;
		share_data->eat_count ++;
	}
	else if (status == SLEEPING)
		message = "\x1b[34mis sleeping\x1b[39m";
	else if (status == THINKING)
		message = "is thinking";
	printf("%d_in_ms %d %s\n", now, philo_id, message);
	pthread_mutex_unlock(&table_data->action_mutex);
}

void	print_die(t_philo *share_data, \
	int philo_id, t_table	*table_data)
{
	char	*message;
	int		now;

	if (table_data->all_living == FALSE)
		return ;
	message = "died";
	now = get_now_time(share_data->table_data->start_time);
	printf("%d_in_ms %d %s\n", now, philo_id, message);
}

// int main(void)
// {
//   	struct timeval tv;

//   	gettimeofday(&tv, NULL);
// 	//   printf("%06d\n", tv.tv_usec);
// 	//   gettimeofday(&tv, NULL);
// 	//   printf("%06d\n", tv.tv_usec);
// 	print_timestamp(tv, 1, 0);
//   	return 0;
// }