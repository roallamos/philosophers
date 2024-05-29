/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:26 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 12:58:08 by rodralva         ###   ########.fr       */
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
	long long		last_ate;
	int				*dead;
	int				*terminate;
	t_arg			arg;
	pthread_mutex_t	*fork;
	struct timeval	tv;
}	t_data;

int			ft_atoi(const char *str);
void		*routine(void *arg);
long long	gettime_ms(struct timeval data);
void		ft_usleep(long long wait, long long time, struct timeval tv);
void		*checker_routine(void *arg);
int			check_dead(t_data *data);
void	*ft_memset(void *buf, int c, size_t len);

#endif
