/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:50:11 by takuokam          #+#    #+#             */
/*   Updated: 2022/12/21 15:26:34 by takuokam         ###   ########.fr       */
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

typedef struct s_philo
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					*fork;
	int					philo_id;
	int					num_philosophers;
	int					someone_is_dead;
	int					status;
	pthread_mutex_t *mutex;
	struct timeval start_time;
	t_fork			**mutex_fork;
}		t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void print_timestamp(struct timeval start_time, int philo_id, int status);

#endif