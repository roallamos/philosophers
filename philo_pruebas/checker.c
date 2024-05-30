/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:08 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 16:04:06 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	check_eat(t_data *data)
{
	
}*/

int	check_dead(t_data *data)
{
	pthread_mutex_lock(data->dead_mutex);
	if (gettime_ms() - data->start_time - data->last_ate > data->arg.time_to_die || *data->dead == 1)
	{
		if (*data->dead != 1)
		{
			pthread_mutex_unlock(data->dead_mutex);
			speak(data, DIE);
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
		/*	if (check_eat(&data[i]))
					return (NULL);*/
			i++;
		}
	}
}
