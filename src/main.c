/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/06 14:26:21 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate(pthread_t **th, t_data **data, t_mutex *mutex, t_arg	arg)
{
	*th = (pthread_t *) malloc(sizeof(pthread_t) * (arg.nb_philos + 1));
	if (!*th)
		return (printf("memory allocation error\n"), 1);
	*data = (t_data *) malloc(sizeof(t_data) * arg.nb_philos);
	if (!*data)
		return (printf("memory allocation error\n"), 1);
	mutex->mutex_fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * (arg.nb_philos));
	if (!mutex->mutex_fork)
		return (printf("memory allocation error\n"), 1);
	mutex->mutex_extra = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * 5);
	if (!mutex->mutex_extra)
		return (printf("memory allocation error\n"), 1);
	return (0);
}

void	ft_free(pthread_t *th, t_data *data, t_mutex mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb && mutex.mutex_fork)
		pthread_mutex_destroy(&mutex.mutex_fork[i++]);
	i = 0;
	while (i < 5 && mutex.mutex_extra)
		pthread_mutex_destroy(&mutex.mutex_extra[i++]);
	if (data)
	{
		if (data->dead)
			free(data->dead);
		if (data->nb_eat)
			free(data->nb_eat);
	}
	free(th);
	free(data);
	if (mutex.mutex_fork)
		free(mutex.mutex_fork);
	if (mutex.mutex_extra)
		free(mutex.mutex_extra);
}

int	terminate(pthread_t *th, t_data *data, t_mutex mutex, int nb)
{
	ft_free(th, data, mutex, nb);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*th;
	t_arg			arg;
	t_data			*data;
	t_mutex			mutex;

	if ((argc != 5 && argc != 6) || !check_args(argv))
		return (0);
	init_args(argv, &arg, argc);
	memset(&mutex, 0, sizeof(t_mutex));
	memset(&data, 0, sizeof(t_data *));
	if (allocate(&th, &data, &mutex, arg))
		return (terminate(th, data, mutex, arg.nb_philos));
	if (init_mutex(mutex.mutex_fork, arg.nb_philos))
		return (terminate(th, data, mutex, arg.nb_philos));
	if (init_mutex(mutex.mutex_extra, 5))
		return (terminate(th, data, mutex, arg.nb_philos));
	if (init_data(data, mutex, arg))
		return (terminate(th, data, mutex, arg.nb_philos));
	init_th(th, data);
	ft_free(th, data, mutex, arg.nb_philos);
	return (0);
}
