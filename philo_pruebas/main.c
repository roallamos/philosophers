/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:25:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/22 17:35:16 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int nb;
	int nb_derecha = 0;
	data_t *data;
	int i = 0;

	data = (data_t *)arg;
	nb = data->philo;
	nb_derecha = nb + 1;
	if (nb_derecha > data->total_philo)
		nb_derecha = 1;
/*	if (data->philo % 2 == 0)
		usleep(100);*/
	while(i < 2 && nb % 2 == 1)
	{
		pthread_mutex_lock(&data->fork[nb - 1]);
		pthread_mutex_lock(&data->fork[nb_derecha - 1]);
		printf("%d\n", data->philo);
		pthread_mutex_unlock(&data->fork[nb_derecha - 1]);
		pthread_mutex_unlock(&data->fork[nb - 1]);
		i++;
	}
	while(i < 2 && nb % 2 == 0)
	{
		pthread_mutex_lock(&data->fork[nb_derecha - 1]);
		pthread_mutex_lock(&data->fork[nb - 1]);
		printf("%d\n", data->philo);
		pthread_mutex_unlock(&data->fork[nb - 1]);
		pthread_mutex_unlock(&data->fork[nb_derecha - 1]);
		i++;
	}
	return(NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	int	i;
	int	nb;
	data_t *data;
	pthread_mutex_t *mutex;

	if (argc == 1)
		return (0);
	nb = ft_atoi(argv[1]);
	i = 0;
	th = (pthread_t *) malloc(sizeof(pthread_t) * nb);
	data = (data_t *) malloc(sizeof(data_t) * nb);
	mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb);
	while(i < nb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		data[i].philo = i + 1;
		data[i].total_philo = nb;
		data[i].fork = mutex;
		if(pthread_create(&th[i], NULL, &routine, &data[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	while (i < nb)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(th);
	free(data);
	return (0);
}
