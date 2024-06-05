/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:17 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/05 17:30:10 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_eat(t_data *data)
{
	pthread_mutex_lock(data->last_ate_mutex);
	data->last_ate = gettime_ms() - data->start_time;
	pthread_mutex_unlock(data->last_ate_mutex);
	printf("%lld %d is eating\n", data->last_ate, data->philo);
	pthread_mutex_lock(data->nb_eat_mutex);
	data->nb_eat[data->philo - 1] += 1;
	pthread_mutex_unlock(data->nb_eat_mutex);
}

void	speak_dead(t_data *data)
{
	pthread_mutex_lock(data->print_mutex);
	printf("%lld %d died\n", gettime_ms() - data->start_time, data->philo);
	pthread_mutex_unlock(data->print_mutex);
}

void	speak(t_data *data, int action)
{
	pthread_mutex_lock(data->print_mutex);
	if (!checker_dead(data))
	{
		if (action == FORK)
			printf("%lld %d has taken a fork\n",
				gettime_ms() - data->start_time, data->philo);
		else if (action == EAT)
			printf_eat(data);
		else if (action == SLEEP)
			printf("%lld %d is sleeping\n",
				gettime_ms() - data->start_time, data->philo);
		else if (action == THINK)
			printf("%lld %d is thinking\n",
				gettime_ms() - data->start_time, data->philo);
	}
	pthread_mutex_unlock(data->print_mutex);
}
