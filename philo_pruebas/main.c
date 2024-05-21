/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:25:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/21 20:19:00 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct	indidual_philo_s
{
	int	philo;
	int	total_philo;
} indidual_philo_t;


typedef struct	data_s
{
	int	philo;
	int	total_philo;
	int	*cambiar;
	pthread_mutex_t *fork;
} data_t;

void	*routine(void *arg)
{
	int nb;
	data_t *data;
	int i = 0;

	data = (data_t *)arg;
	nb = data->philo;
	while(i < 1000000)
	{
		pthread_mutex_lock(&data->fork[nb]);
		*data->cambiar += 1;
		pthread_mutex_unlock(&data->fork[nb]);
		i++;
	}
	printf("%d\n", nb);
	return(NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	int	i;
	int	nb;
	data_t *data;
	pthread_mutex_t *mutex;
	int	pruebas = 0;

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
		data[i].cambiar = &pruebas;
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
	printf("pruebas %d", pruebas);
	while (i < nb)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(th);
	free(data);
	return (0);
}
