/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/30 12:46:04 by rodralva         ###   ########.fr       */
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

void	init_mutex(pthread_mutex_t *mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
}

void	init_th(pthread_t *th, t_data *data)
{
	int				i;
	struct timeval	tv;

	i = 0;
	gettimeofday(&tv, NULL);
	while (i < data->arg.nb_philos)
	{
		data[i].tv = tv;
		if (pthread_create(&th[i], NULL, &routine, &data[i]) != 0)
			exit (0);
		i++;
		if (i == data->arg.nb_philos)
		{
			if (pthread_create(&th[i], NULL, &checker_routine, data))
					exit (0);
		}
	}
	i = 0;
	while (i <= data->arg.nb_philos)
		pthread_join(th[i++], NULL);
}

void	init_data(t_data *data, t_mutex mutex, t_arg arg)
{
	int				*dead;	
	int				i;
	
	dead = (int *) malloc(4);
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
		i++;
	}
}

void	ft_free(pthread_t *th, t_data *data, t_mutex mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		pthread_mutex_destroy(&mutex.mutex_fork[i++]);
	pthread_mutex_destroy(&mutex.mutex_extra[0]);
	pthread_mutex_destroy(&mutex.mutex_extra[1]);
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
	data = (t_data *) malloc(sizeof(t_data) * arg.nb_philos);
	mutex.mutex_fork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (arg.nb_philos));
	mutex.mutex_extra = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 2);
	init_mutex(mutex.mutex_fork, arg.nb_philos);
	init_mutex(mutex.mutex_extra, 2);
	init_data(data, mutex, arg);
	init_th(th, data);
	ft_free(th, data, mutex, arg.nb_philos);
	return (0);
}
