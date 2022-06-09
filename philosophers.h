/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:12:19 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 16:03:33 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct s_mutexes
{
	pthread_mutex_t mutex;
	pthread_mutex_t print;
	int i;
	struct s_mutexes *next;
} t_mutexes ;

typedef struct s_philos
{
	pthread_t	thread;
	int	n_ph;
	long stamp;
	long  stamp_u;
	int rank;
	long death;
	long eat;
	long sleep;
	int eating;
	t_mutexes *mutexes;
} t_philos ;



int	ft_atoi(const char *str);
int	input_eval(char **av);
int	ft_strlen(const char *s);
int mutexes_destroy(t_philos *philos, int rank);
int	philosophers(t_philos *philo);
void	*routine(void *i);
void	eating(t_philos *philo);
long	what_time();
void free_data(t_philos *philos);

#endif
