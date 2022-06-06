/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:12:19 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/06 20:53:45 by ozahir           ###   ########.fr       */
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

typedef struct s_philos
{
	pthread_t	*thread;
	int	n_ph;
	int rank;
	int death;
	int eat;
	int sleep;
	int eating;
	pthread_mutex_t *right_f;
	pthread_mutex_t left_f;

} t_philos ;



int	ft_atoi(const char *str);
int	input_eval(char **av);
int	ft_strlen(const char *s);
int mutexes_destroy(t_philos *philos, int rank);
void	philosophers(t_philos *philo);
void	*routine(t_philos philos);
void	eating(t_philos philo);

#endif
