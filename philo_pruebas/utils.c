/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:24:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 20:49:59 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long wait, long long time, struct timeval tv)
{
	long long	real_time;

	real_time = 0;
	while (real_time < time + wait)
		real_time = gettime_ms(tv);
}

long long	gettime_ms(struct timeval data)
{
	struct timeval	tv;
	long long		miliseconds;
	long long		data_ms;

	data_ms = (data.tv_sec * 1000) + (data.tv_usec / 1000);
	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds - data_ms);
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
