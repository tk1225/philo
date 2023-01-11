/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:50:11 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/11 19:10:30 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

# define TAKEN_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

# define INUSE 1
# define AVAILABLE 0

# define TRUE 1
# define FALSE 0

typedef struct s_fork
{
	int					status;
	pthread_mutex_t 	mutex;
}		t_fork;

typedef struct s_table
{
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	int					num_philosophers;
	int					someone_is_dead;
	struct timeval start_time;
}		t_table;

typedef struct s_philo
{
	t_table				*table_data;
	int					philo_id;
	int					status;
	size_t					last_meal_time;
	t_fork				**mutex_fork;
}		t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void print_timestamp(struct timeval start_time, int philo_id, int status);
void mutex_lock(t_philo *share_data, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork);
void mutex_unlock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork);

#endif