/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:24:00 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/04 14:24:46 by rodralva         ###   ########.fr       */
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
	int	*dead;	
	int	*eat;
	int	i;

	dead = (int *) malloc(4);
	if (!dead)
	{
		printf("memory allocation error\n");
		return (1);
	}
	*dead = 0;
	eat = (int *) malloc(4 * arg.nb_philos);
	if (!eat)
	{
		printf("memory allocation error\n");
		return (1);
	}
	memset(eat, 0, 4 * arg.nb_philos);
	i = 0;
	while (i < arg.nb_philos)
	{
		data[i].philo = i + 1;
		data[i].arg = arg;
		data[i].fork = mutex.mutex_fork;
		data[i].dead = dead;
		data[i].last_ate = 0;
		data[i].nb_eat = eat;
		data[i].print_mutex = &mutex.mutex_extra[0];
		data[i].dead_mutex = &mutex.mutex_extra[1];
		data[i].lock_mutex = &mutex.mutex_extra[2];
		data[i].nb_eat_mutex = &mutex.mutex_extra[3];
		i++;
	}
	return (0);
}
