/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 16:59:23 by ozahir           ###   ########.fr       */
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
