/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:17 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 16:53:28 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	speak(t_data *data, int action)
{
	pthread_mutex_lock(data->print_mutex);
	pthread_mutex_lock(data->dead_mutex);
	if (!*data->dead)
	{
		if (action == FORK)
			printf("%lld %d has taken a fork\n", gettime_ms() - data->start_time, data->philo);
		else if (action == EAT)
		{
			data->last_ate = gettime_ms() - data->start_time;
			printf("%lld %d is eating\n", data->last_ate, data->philo);
		}
		else if (action == SLEEP)
			printf("%lld %d is sleeping\n", gettime_ms() - data->start_time, data->philo);
		else if (action == THINK)
			printf("%lld %d is thinking\n", gettime_ms() - data->start_time, data->philo);
		else if (action == DIE)
		{
			printf("%lld %d died\n", gettime_ms() - data->start_time, data->philo);
			*data->dead = 1;
		}
	}
	pthread_mutex_unlock(data->dead_mutex);
	pthread_mutex_unlock(data->print_mutex);
}
