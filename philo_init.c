/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:53 by takuokam          #+#    #+#             */
/*   Updated: 2022/12/14 17:19:20 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_philo *share_data;
	int		num_philosophers;
	int *fork;

	if (argc <= 1)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	num_philosophers = ft_atoi(argv[1]);
	share_data->time_to_die = ft_atoi(argv[2]);
	share_data->time_to_eat = ft_atoi(argv[3]);
	share_data->time_to_sleep = ft_atoi(argv[4]);

	fork = (int *)ft_calloc(num_philosophers, sizeof(int));

	return (0);
}