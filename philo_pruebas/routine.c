/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:46:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 17:02:55 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_data *data, int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->fork[fork_1]);
	speak(data, FORK);
	if (data->arg.nb_philos == 1)
	{
		pthread_mutex_unlock(&data->fork[fork_1]);
		ft_usleep(data->arg.time_to_die);
		return (1);
	}
	pthread_mutex_lock(&data->fork[fork_2]);
	speak(data, FORK);
	speak(data, EAT);
	ft_usleep(data->arg.time_to_eat);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
	return (0);
}

int	philo_sleep(t_data *data)
{
	speak(data, SLEEP);
	ft_usleep(data->arg.time_to_sleep);
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
		if (nb % 2 == 1)
		{
			if (eat(data, nb - 1, nb_derecha - 1) == 1)
				return (NULL);
		}
		else
			eat(data, nb_derecha - 1, nb - 1);
		philo_sleep(data);
		speak(data, THINK);
		pthread_mutex_lock(data->dead_mutex);
		if (*data->dead)
		{
			pthread_mutex_unlock(data->dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(data->dead_mutex);
	}
}
