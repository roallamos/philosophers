/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:46:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/09/25 20:52:41 by rodralva         ###   ########.fr       */
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
		if (data->arg.nb_philos <= 3)
			pthread_mutex_unlock(data->lock_mutex);
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

void	philo_sleep(t_data *data)
{
	speak(data, SLEEP);
	ft_usleep(data->arg.time_to_sleep);
}

int	philo_eat(t_data *data, int left_fork, int right_fork)
{
	if (left_fork != data->arg.nb_philos)
	{
		if (eat(data, left_fork - 1, right_fork - 1) == 1)
			return (1);
	}
	else
	{
		if (eat(data, right_fork - 1, left_fork - 1) == 1)
			return (1);
	}
	return (0);
}

void	philo_think(t_data *data)
{
	long	time;
	
	time = (data->arg.time_to_eat * 2) - data->arg.time_to_sleep;
	ft_usleep(time * 0.42);
	speak(data, THINK);
}

void	*routine(void *arg)
{
	int		fork;
	int		right_fork;
	t_data	*data;

	data = (t_data *)arg;
	fork = data->philo;
	right_fork = fork + 1;
	if (right_fork > data->arg.nb_philos)
		right_fork = 1;
	if (data->philo % 2 == 1 && data->arg.nb_philos != 1)
		ft_usleep(50);
	while (1)
	{
		if (philo_eat(data, fork, right_fork))
			return (NULL);
		philo_sleep(data);
		philo_think(data);
		pthread_mutex_lock(data->dead_mutex);
		if (*data->dead)
		{
			pthread_mutex_unlock(data->dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(data->dead_mutex);
	}
}
