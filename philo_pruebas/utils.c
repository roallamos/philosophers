/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:24:30 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 12:54:24 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *buf, int c, size_t len)
{
	size_t			i;
	unsigned char	*t;

	i = 0;
	t = (unsigned char *) buf;
	while (i < len)
	{
		t[i] = c;
		i++;
	}
	return (t);
}

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

	data_ms = (data.tv_sec * 1000LL) + (data.tv_usec / 1000);
	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
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
