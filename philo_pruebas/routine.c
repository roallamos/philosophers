/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:24:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/28 16:44:15 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *data, int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->fork[fork_1]);
	printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
	pthread_mutex_lock(&data->fork[fork_2]);
	printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
	printf("%lld %d is eating\n", gettime_ms(data->tv), data->philo);
	ft_usleep(data->arg.time_to_eat, gettime_ms(data->tv), data->tv);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
}

void	philo_sleep(t_data *data)
{
	printf("%lld %d is sleeping\n", gettime_ms(data->tv), data->philo);
	ft_usleep(data->arg.time_to_sleep, gettime_ms(data->tv), data->tv);
}

void	*routine(void *arg)
{
	int		nb;
	int		nb_derecha;
	t_data	*data;

	data = (t_data *)arg;
	nb = data->philo;
	nb_derecha = nb + 1;
	if (nb_derecha > data->arg.nb_philos)
		nb_derecha = 1;
	if (nb % 2 == 1)
		eat(data, nb - 1, nb_derecha - 1);
	else
		eat(data, nb_derecha - 1, nb - 1);
	philo_sleep(data);
	printf("%lld %d is thinking\n", gettime_ms(data->tv), data->philo);
	return (NULL);
}
