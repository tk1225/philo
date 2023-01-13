/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:41:26 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/13 20:20:11 by takuokam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	each_fork_init(t_fork **fork_struct_list, int i)
{
	t_fork	*each_fork;

	each_fork = (t_fork *)malloc(sizeof(t_fork));
	pthread_mutex_init(&each_fork->mutex, NULL);
	each_fork->status = AVAILABLE;
	fork_struct_list[i] = each_fork;
}

static void	fork_init(t_philo *share_data)
{
	t_fork	**fork_struct_list;
	int		i;

	fork_struct_list = (t_fork **)malloc(sizeof(t_fork *) * \
	share_data->table_data->num_philosophers);
	i = 0;
	while (i < share_data->table_data->num_philosophers)
	{
		each_fork_init(fork_struct_list, i);
		i ++;
	}
	share_data->mutex_fork = fork_struct_list;
	pthread_mutex_init(&share_data->table_data->action_mutex, NULL);
}

static t_philo	*share_data_init(int argc, char *argv[])
{
	t_philo	*share_data;

	if (argc <= 1 || argc <= 4)
		exit(EXIT_FAILURE);
	share_data = (t_philo *)malloc(sizeof(t_philo));
	share_data->table_data = (t_table *)malloc(sizeof(t_table));
	share_data->table_data->num_philosophers = ft_atoi(argv[1]);
	share_data->table_data->time_to_die = ft_atoi(argv[2]);
	share_data->table_data->time_to_eat = ft_atoi(argv[3]);
	share_data->table_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		share_data->table_data->max_eat_count = ft_atoi(argv[5]);
	share_data->table_data->someone_is_dead = FALSE;
	return (share_data);
}

int	main(int argc, char *argv[])
{
	t_philo	*share_data;

	share_data = share_data_init(argc, argv);
	fork_init(share_data);
	create_thread(share_data, share_data->table_data->num_philosophers);
	return (0);
}
