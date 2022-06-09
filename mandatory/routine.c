/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:58:43 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 17:02:43 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philos *philo)
{
	pthread_mutex_lock(&get_mutex(philo->mutexes)->print);
	printf("%lu %d sleeping\n", (what_time() - philo->stamp), philo->rank + 1);
	pthread_mutex_unlock(&get_mutex(philo->mutexes)->print);
	usleep(philo->sleep * 1000);
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(&get_mutex(philo->mutexes)->print);
	printf("%lu %d is thinking\n",
		(what_time() - philo->stamp), philo->rank + 1);
	pthread_mutex_unlock(&get_mutex(philo->mutexes)->print);
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutexes->mutex);
	pthread_mutex_lock(&get_mutex(philo->mutexes)->print);
	printf("%lu %d has taken a left fork\n",
		(what_time() - philo->stamp), philo->rank + 1);
	pthread_mutex_unlock(&get_mutex(philo->mutexes)->print);
	pthread_mutex_lock(&philo->mutexes->next->mutex);
	pthread_mutex_lock(&get_mutex(philo->mutexes)->print);
	printf("%lu %d has taken a right fork\n",
		(what_time() - philo->stamp), philo->rank + 1);
	printf("%lu %d is eating\n", (what_time() - philo->stamp), philo->rank + 1);
	pthread_mutex_unlock(&get_mutex(philo->mutexes)->print);
	philo->stamp_u = what_time();
	usleep(philo->eat * 1000);
	pthread_mutex_unlock(&philo->mutexes->mutex);
	pthread_mutex_unlock(&philo->mutexes->next->mutex);
}

void	mini_routine(t_philos *philo)
{
	eating(&philo[0]);
	sleeping(&philo[0]);
	thinking(&philo[0]);
}

void	*routine(void *phil)
{
	t_philos	*philo;

	philo = (t_philos *)(phil);
	if ((philo[0].rank % 2) != 0)
		usleep(100);
	if (philo[0].eating == 0)
		return (NULL);
	else if (philo[0].eating == -1)
	{
		while (1)
		{
			mini_routine(&philo[0]);
		}
	}
	else if (philo[0].eating > 0)
	{
		while (philo[0].eating)
		{
			eating(&philo[0]);
			sleeping(&philo[0]);
			thinking(&philo[0]);
			philo[0].eating--;
		}
	}
	return (NULL);
}
