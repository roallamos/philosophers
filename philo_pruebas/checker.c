/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:08 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 12:39:37 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
{
	if (gettime_ms(data->tv) - data->last_ate > data->arg.time_to_die || *data->dead == 1)
	{
		if (*data->dead != 1)
		{
			*data->dead = 1;
			printf("%lld %d died\n", gettime_ms(data->tv), data->philo);
		}
		return (1);
	}
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
