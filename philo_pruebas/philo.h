/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:26 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 16:05:13 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_mutex
{
		pthread_mutex_t *mutex_fork;
		pthread_mutex_t *mutex_extra;
}	t_mutex;

typedef struct s_arg
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
}	t_arg;

typedef struct s_data
{
	int				philo;
	int				*dead;
	long long		last_ate;
	long long		start_time;
	int				nb_eat;
	t_arg			arg;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*lock_mutex;
	struct timeval	tv;
}	t_data;

int			ft_atoi(const char *str);
void		*routine(void *arg);
long long	gettime_ms(void);
void		ft_usleep(long long wait);
void		*checker_routine(void *arg);
int			check_dead(t_data *data);
void		*ft_memset(void *buf, int c, size_t len);
void		speak(t_data *data, int action);

#endif
