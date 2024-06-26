/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:24:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/05 15:38:05 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker_dead(t_data *data)
{
	pthread_mutex_lock(data->dead_mutex);
	if (*data->dead == 1)
	{
		pthread_mutex_unlock(data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->dead_mutex);
	return (0);
}

void	ft_usleep(long long wait)
{
	long long	start_time;

	start_time = gettime_ms();
	while (gettime_ms() < start_time + wait)
		usleep(100);
}

long long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	s;

	i = 0;
	nb = 0;
	s = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (s == 1)
		nb = -nb;
	return (nb);
}
