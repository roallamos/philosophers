/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:26 by rodralva          #+#    #+#             */
/*   Updated: 2024/05/22 19:33:20 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct data_s
{
	int	philo;
	int	total_philo;
	pthread_mutex_t *fork;
} data_t;

int	ft_atoi(const char *str);
void	*routine(void *arg);

#endif
