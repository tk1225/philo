/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:08:35 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/18 19:51:37 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_timestamp(struct timeval start_time, \
	int philo_id, int status, t_table	*table_data)
{
	char	*message;

	pthread_mutex_lock(&table_data->action_mutex);
	if (table_data->all_living == FALSE)
		return ;
	message = "";
	if (status == TAKEN_FORK)
		message = "has taken a fork";
	else if (status == EATING)
	{
		message = "\x1b[31mis eating\x1b[39m";
	}
	else if (status == SLEEPING)
		message = "\x1b[34mis sleeping\x1b[39m";
	else if (status == THINKING)
		message = "is thinking";
	else if (status == DIED)
		message = "died";
	// get_now_time(start_time
	// (void)start_time;
	// (void)message;
	// (void)philo_id;
	
	// ft_putstr_fd("test", 1);
	
	printf("%d_in_ms %d %s\n", get_now_time(start_time) ,philo_id, message);
	pthread_mutex_unlock(&table_data->action_mutex);
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