/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:24:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/28 22:41:46 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
{
	if (gettime_ms(data->tv) - data->last_ate > data->arg.time_to_die || *data->dead == 1)
	{
		printf("i am %d\n", data->philo);
		if (*data->dead != 1)
		{
			*data->dead = 1;
			printf("%lld %d died\n", gettime_ms(data->tv), data->philo);
		}
		return (1);
	}
	return (0);
}

int	eat(t_data *data, int fork_1, int fork_2)
{
	if (check_dead(data))
		return (1);
	pthread_mutex_lock(&data->fork[fork_1]);
	printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
	pthread_mutex_lock(&data->fork[fork_2]);
	printf("%lld %d has taken a fork\n", gettime_ms(data->tv), data->philo);
	data->last_ate = gettime_ms(data->tv);
	printf("%lld %d is eating\n", data->last_ate, data->philo);
	ft_usleep(data->arg.time_to_eat, gettime_ms(data->tv), data->tv);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
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
	while (1)
	{
		if (nb % 2 == 1 && check_dead(data) == 0)
			eat(data, nb - 1, nb_derecha - 1);
		else if (check_dead(data) == 0)
			eat(data, nb_derecha - 1, nb - 1);
		else if (check_dead(data))
			return (NULL);
		if (check_dead(data) == 0)
			philo_sleep(data);
		else
			return (NULL);
		if (check_dead(data) == 0)
			printf("%lld %d is thinking\n", gettime_ms(data->tv), data->philo);
	}
}
