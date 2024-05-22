/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:25:38 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/22 20:30:22 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_init(&mutex[i++], NULL);
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
		pthread_join(th[i++], NULL);
	i = 0;
	while (i < nb)
		pthread_mutex_destroy(&mutex[i++]);
	free(th);
	free(data);
	free(mutex);
	return (0);
}
