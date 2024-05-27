/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:24:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/27 18:20:26 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *data, int fork_1, int fork_2)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&data->fork[fork_1]);
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n",tv.tv_usec - data->tv.tv_usec, data->philo);
	pthread_mutex_lock(&data->fork[fork_2]);
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n",tv.tv_usec - data->tv.tv_usec, data->philo);
	usleep(data->arg.time_to_eat);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
}

void	philo_sleep(t_data *data)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", tv.tv_usec - data->tv.tv_usec, data->philo);
	usleep(data->arg.time_to_sleep);
}

void	*routine(void *arg)
{
	int		nb;
	int		nb_derecha;
	t_data	*data;
	struct timeval tv;

	data = (t_data *)arg;
	nb = data->philo;
	nb_derecha = nb + 1;
//	while(1){
	if (nb_derecha > data->arg.nb_philos)
		nb_derecha = 1;
	if (nb % 2 == 1)
		eat(data, nb - 1, nb_derecha - 1);
	else
		eat(data, nb_derecha - 1, nb - 1);
	philo_sleep(data);
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", tv.tv_usec - data->tv.tv_usec, data->philo);
	return (NULL);
}
