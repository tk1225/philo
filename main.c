/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:41:26 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/27 14:10:15 by takumasaoka      ###   ########.fr       */
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

	share_data = (t_philo *)malloc(sizeof(t_philo));
	share_data->table_data = (t_table *)malloc(sizeof(t_table));
	share_data->table_data->num_philosophers = ft_atoi(argv[1]);
	share_data->table_data->time_to_die = ft_atoi(argv[2]);
	share_data->table_data->time_to_eat = ft_atoi(argv[3]);
	share_data->table_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		share_data->table_data->max_eat_count = ft_atoi(argv[5]);
	share_data->table_data->all_living = TRUE;
	return (share_data);
}

int	check_table_data(t_table *table_data, int argc)
{
	if (((table_data->max_eat_count <= 0) && argc == 6) \
	|| (table_data->num_philosophers <= 0) || \
	(table_data->time_to_eat <= 0) || (table_data->time_to_die <= 0) \
	|| table_data->time_to_sleep <= 0 || (table_data->num_philosophers >= 201))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_philo	*share_data;
	int		i;

	if (argc <= 1 || argc <= 4)
		return (0);
	share_data = share_data_init(argc, argv);
	if (check_table_data(share_data->table_data, argc) == FALSE)
	{
		free(share_data->table_data);
		free(share_data);
		write(0, "error\n", 6);
		return (0);
	}
	fork_init(share_data);
	create_thread(share_data, share_data->table_data->num_philosophers);
	i = 0;
	while (i < share_data->table_data->num_philosophers)
	{
		free(share_data->mutex_fork[i]);
		i ++;
	}
	free(share_data->mutex_fork);
	free(share_data);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }
