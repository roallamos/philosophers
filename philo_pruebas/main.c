/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:45:22 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/29 21:21:43 by rodralva         ###   ########.fr       */
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
	while (i <= nb + 1)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
}

void	init_th(pthread_t *th, t_data *data, pthread_mutex_t *mutex, t_arg arg)
{
	int				i;
	int				*dead;
	struct timeval	tv;

	i = 0;
	dead = (int *) malloc(4);
	*dead = 0;
	gettimeofday(&tv, NULL);
	while (i < arg.nb_philos)
	{
		data[i].philo = i + 1;
		data[i].arg = arg;
		data[i].fork = mutex;
		data[i].dead = dead;
		data[i].tv = tv;
		data[i].last_ate = 0;
		data[i].print_mutex = &mutex[arg.nb_philos];
		data[i].dead_mutex = &mutex[arg.nb_philos + 1];
		data[i].th = th;
		if (pthread_create(&th[i], NULL, &routine, &data[i]) != 0)
			exit (0);
		i++;
		if (i == arg.nb_philos)
		{
			if (pthread_create(&th[i], NULL, &checker_routine, data))
					exit (0);
		}
	}
}

void	ft_free(pthread_t *th, t_data *data, pthread_mutex_t *mutex, int nb)
{
	int	i;

	i = 0;
	while (i <= nb + 1)
		pthread_mutex_destroy(&mutex[i++]);
	free(data->dead);
	free(th);
	free(data);
	free(mutex);
}

int	main(int argc, char **argv)
{
	pthread_t		*th;
	int				i;
	t_arg			arg;
	t_data			*data;
	pthread_mutex_t	*mutex;

	if (argc < 2 || argc > 6)
		return (0);
	init_args(argv, &arg, argc);
	th = (pthread_t *) malloc(sizeof(pthread_t) * arg.nb_philos + 1);
	data = (t_data *) malloc(sizeof(t_data) * arg.nb_philos);
	mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (arg.nb_philos + 2));
	init_mutex(mutex, arg.nb_philos);
	init_th(th, data, mutex, arg);
	i = 0;
	while (i <= arg.nb_philos)
		pthread_join(th[i++], NULL);
	ft_free(th, data, mutex, arg.nb_philos);
	return (0);
}
