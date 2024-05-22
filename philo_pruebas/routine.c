/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:24:24 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/22 20:30:18 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(data_t *data, int fork_1, int fork_2)
{
	pthread_mutex_lock(&data->fork[fork_1]);
	pthread_mutex_lock(&data->fork[fork_2]);
	printf("philo nº %d is eating\n", data->philo);
	pthread_mutex_unlock(&data->fork[fork_2]);
	pthread_mutex_unlock(&data->fork[fork_1]);
}

void	*routine(void *arg)
{
	int nb;
	int nb_derecha = 0;
	data_t *data;

	data = (data_t *)arg;
	nb = data->philo;
	nb_derecha = nb + 1;
	if (nb_derecha > data->total_philo)
		nb_derecha = 1;
	if(nb % 2 == 1)
		eat(data, nb - 1, nb_derecha - 1);
	else
		eat(data, nb_derecha - 1, nb - 1);
	return(NULL);
}
