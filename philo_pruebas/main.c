/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 19:33:45 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(char **argv, t_arg *arg, int argc)
{
	arg->nb_philos = ft_atoi(argv[1]);
	arg->time_to_die = (ft_atoi(argv[2]));
	arg->time_to_eat = (ft_atoi(argv[3]));
	arg->time_to_sleep = (ft_atoi(argv[4]));
	if (argc == 6)
		arg->nb_must_eat = (ft_atoi(argv[5]));
	else
		arg->nb_must_eat = -1;
}

int	init_mutex(pthread_mutex_t *mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
		{
				printf("mutex init error\n");
				return (1);
		}
		i++;
	}
	return (0);
}

int	init_th(pthread_t *th, t_data *data)
{
	int			i;
	long long	time;

	i = 0;
	time = gettime_ms();
	while (i < data->arg.nb_philos)
	{
		data[i].start_time = time;
		if (pthread_create(&th[i], NULL, &routine, &data[i]))
		{
			printf("thread chreation error\n");
			return (1);
		}
		i++;
		if (i == data->arg.nb_philos)
		{
			if (pthread_create(&th[i], NULL, &checker_routine, data))
			{
				printf("thread chreation error\n");
				return (1);
			}
		}
	}
	i = 0;
	while (i <= data->arg.nb_philos)
	{
		if (pthread_join(th[i++], NULL))
		{
			printf("thread chreation error\n");
			return (1);
		}
	}
	return (0);
}

int	init_data(t_data *data, t_mutex mutex, t_arg arg)
{
	int				*dead;	
	int				i;
	
	dead = (int *) malloc(4);
	if (!dead)
	{
			printf("memory allocation error\n");
			return (1);
	}
	*dead = 0;
	i = 0;
	while (i < arg.nb_philos)
	{
		data[i].philo = i + 1;
		data[i].arg = arg;
		data[i].fork = mutex.mutex_fork;
		data[i].dead = dead;
		data[i].last_ate = 0;
		data[i].print_mutex = &mutex.mutex_extra[0];
		data[i].dead_mutex = &mutex.mutex_extra[1];
		data[i].lock_mutex = &mutex.mutex_extra[2];
		i++;
	}
	return (0);
}

void	ft_free(pthread_t *th, t_data *data, t_mutex mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		pthread_mutex_destroy(&mutex.mutex_fork[i++]);
	pthread_mutex_destroy(&mutex.mutex_extra[0]);
	pthread_mutex_destroy(&mutex.mutex_extra[1]);
	pthread_mutex_destroy(&mutex.mutex_extra[2]);
	free(data->dead);
	free(th);
	free(data);
	free(mutex.mutex_fork);
	free(mutex.mutex_extra);
}

int	main(int argc, char **argv)
{
	pthread_t		*th;
	t_arg			arg;
	t_data			*data;
	t_mutex			mutex;

	if (argc < 2 || argc > 6)
		return (0);
	init_args(argv, &arg, argc);
	th = (pthread_t *) malloc(sizeof(pthread_t) * arg.nb_philos + 1);
	if (!th)
	{
			printf("memory allocation error\n");
			return (1);
	}
	data = (t_data *) malloc(sizeof(t_data) * arg.nb_philos);
	if (!data)
	{
			printf("memory allocation error\n");
			return (1);
	}
	mutex.mutex_fork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (arg.nb_philos));
	if (!mutex.mutex_fork)
	{
			printf("memory allocation error\n");
			return (1);
	}
	mutex.mutex_extra = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 3);
	if (!mutex.mutex_extra)
	{
			printf("memory allocation error\n");
			return (1);
	}
	init_mutex(mutex.mutex_fork, arg.nb_philos);
	init_mutex(mutex.mutex_extra, 3);
	init_data(data, mutex, arg);
	init_th(th, data);
	ft_free(th, data, mutex, arg.nb_philos);
	return (0);
}
