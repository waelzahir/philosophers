/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 15:55:16 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mutexes	*get_mutex(t_mutexes *mutexes)
{
	t_mutexes	*temp;

	temp = mutexes;
	while (1)
	{
		if (temp->i == 100)
			return (temp);
			temp = temp->next;
	}
	return (NULL);
}

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
			eating(&philo[0]);
			sleeping(&philo[0]);
			thinking(&philo[0]);
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

int	all_eaten(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].n_ph)
	{
		if (philos[i].eating != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*watcher_g(void	*phil)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = phil;
	while (i < philos[0].n_ph)
	{
		if (philos[i].eating != 0)
		{
			if (philos[i].death < (what_time() - philos[i].stamp_u))
			{
				pthread_mutex_lock(&philos[0].mutexes->print);
				printf("%ld %d died\n",
					(what_time() - philos[0].stamp), philos[i].rank + 1);
				return (NULL);
			}
		}
		if (all_eaten(philos) == 0)
			break ;
		i++;
		usleep(10);
		if (i == (philos[0].n_ph))
			i = 0;
	}
	return (NULL);
}

int	philosophers(t_philos *philo)
{
	int			i;
	pthread_t	watcher;

	i = 0;
	if (pthread_mutex_init(&philo[0].mutexes->print, NULL) == -1)
		return (0);
	philo[0].mutexes->i = 100;
	while (i < philo[0].n_ph)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	pthread_create(&watcher, NULL, &watcher_g, philo);
	if (pthread_join(watcher, NULL) == 0)
		return (0);
	return (0);
}
