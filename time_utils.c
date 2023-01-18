/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:40:20 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/18 20:13:18 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_now_time(struct timeval start_time)
{
	int				ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - start_time.tv_sec) * 1000 + \
	(now.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

size_t	get_mili_sec(void)
{
	struct timeval	now;
	size_t			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	return (ms);
}

void	sleep_on_time(size_t sleep_time_ms)
{
	size_t			ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	while (get_mili_sec() < ms + sleep_time_ms)
		usleep(200);
}
