/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:24:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/23 16:57:45 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *data, int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->fork[fork_1]);
	printf("%d philo nº %d has taken a fork\n", gettimeofday(), data->philo);
	pthread_mutex_lock(&data->fork[fork_2]);
	printf("philo nº %d is eating\n", data->philo);
	usleep(data->arg.time_to_eat);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
}

void	philo_sleep(t_data *data)
{
	printf("philo nº %d is sleeping\n", data->philo);
	usleep(data->arg.time_to_sleep);
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
	return (NULL);
}
