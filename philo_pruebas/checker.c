/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:08 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 17:40:30 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
{
	pthread_mutex_lock(data->dead_mutex);
	if (gettime_ms(data->tv) - data->last_ate > data->arg.time_to_die || *data->dead == 1)
	{
		if (*data->dead != 1)
		{
			pthread_mutex_unlock(data->dead_mutex);
			speak(data, DIE);
			pthread_mutex_lock(data->dead_mutex);
			*data->dead = 1;
			pthread_mutex_unlock(data->dead_mutex);
		}
		else
			pthread_mutex_unlock(data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->dead_mutex);
	return (0);
}

void	*checker_routine(void *arg)
{
	int i;
	t_data	*data;

	data = arg;
	while (1)
	{
		i = 0;
		while (i < data->arg.nb_philos)
		{
			if (check_dead(&data[i]))
					return (NULL);
			i++;
		}
	}
}
