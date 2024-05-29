/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:46:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 13:55:03 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_data *data, int fork_1, int fork_2)
{
	if (!*data->dead)
	{
		pthread_mutex_lock(&data->fork[fork_1]);
		if (!*data->dead)
			printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
		pthread_mutex_lock(&data->fork[fork_2]);
		if (!*data->dead)
			printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
		if (!*data->dead)
		{
			data->last_ate = gettime_ms(data->tv);
			printf("%lld %d is eating\n", data->last_ate, data->philo);
			ft_usleep(data->arg.time_to_eat, gettime_ms(data->tv), data->tv);
		}
		pthread_mutex_unlock(&data->fork[fork_2]);
		pthread_mutex_unlock(&data->fork[fork_1]);
	}
	return (0);
}

int	philo_sleep(t_data *data)
{
	printf("%lld %d is sleeping\n", gettime_ms(data->tv), data->philo);
	ft_usleep(data->arg.time_to_sleep, gettime_ms(data->tv), data->tv);
	return (0);
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
//	while (1)
//	{
	if (nb % 2 == 1 && !*data->dead)
		eat(data, nb - 1, nb_derecha - 1);
	else if (!*data->dead)
		eat(data, nb_derecha - 1, nb - 1);
	if (!*data->dead)
		philo_sleep(data);
	if (!*data->dead)
		printf("%lld %d is thinking\n", gettime_ms(data->tv), data->philo);
//	}
	return (NULL);
}
