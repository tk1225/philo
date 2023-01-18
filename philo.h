/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:50:11 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/18 19:46:13 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

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
	pthread_mutex_t		mutex;
}		t_fork;

typedef struct s_table
{
	long long int					time_to_die;
	long long int					time_to_eat;
	long long int					time_to_sleep;
	int								num_philosophers;
	int								all_living;
	int								max_eat_count;
	struct timeval					start_time;
	pthread_mutex_t					action_mutex;
}		t_table;

typedef struct s_philo
{
	t_table				*table_data;
	int					philo_id;
	int					status;
	long long int		last_meal_time;
	int					eat_count;
	t_fork				**mutex_fork;
}		t_philo;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	print_timestamp(struct timeval start_time, \
int philo_id, int status, t_table *table_data);
void	mutex_lock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork);
void	mutex_unlock(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork);
int		get_now_time(struct timeval start_time);
size_t	get_mili_sec(void);
void	*philosophers(void *p);
void	sleep_on_time(size_t sleep_time_ms);
void	*referee(void *p);
void	create_thread(t_philo *share_data, int num_philosophers);
void	ft_putstr_fd(char *s, int fd);

#endif