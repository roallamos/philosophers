/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:25:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/28 16:43:44 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(char **argv, t_arg *arg)
{
	arg->nb_philos = ft_atoi(argv[1]);
	arg->time_to_die = (ft_atoi(argv[2]));
	arg->time_to_eat = (ft_atoi(argv[3]));
	arg->time_to_sleep = (ft_atoi(argv[4]));
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

void	init_th(pthread_t *th, t_data *data, pthread_mutex_t *mutex, t_arg arg)
{
	int				i;
	struct timeval	tv;

	i = 0;
	gettimeofday(&tv, NULL);
	while (i < arg.nb_philos)
	{
		data[i].philo = i + 1;
		data[i].arg = arg;
		data[i].fork = mutex;
		data[i].tv = tv;
		if (pthread_create(&th[i], NULL, &routine, &data[i]) != 0)
			exit (0);
		i++;
	}
}

void	ft_free(pthread_t *th, t_data *data, pthread_mutex_t *mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		pthread_mutex_destroy(&mutex[i++]);
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

	if (argc == 1)
		return (0);
	init_args(argv, &arg);
	th = (pthread_t *) malloc(sizeof(pthread_t) * arg.nb_philos);
	data = (t_data *) malloc(sizeof(t_data) * arg.nb_philos);
	mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * arg.nb_philos);
	init_mutex(mutex, arg.nb_philos);
	init_th(th, data, mutex, arg);
	i = 0;
	while (i < arg.nb_philos)
		pthread_join(th[i++], NULL);
	ft_free(th, data, mutex, arg.nb_philos);
	return (0);
}
