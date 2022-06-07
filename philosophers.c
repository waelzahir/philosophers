/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/07 21:43:42 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philos philo)
{
	printf("%lu %d sleeping\n", (what_time() - philo.stamp),philo.rank + 1);
	usleep(philo.sleep * 1000);
}
void	thinking(t_philos philo)
{
	printf("%lu %d is thinking\n",(what_time() - philo.stamp), philo.rank + 1);
}
void	eating(t_philos philo)
{
	pthread_mutex_lock(&philo.mutexes->mutex);
	printf("%lu %d has taken a left fork\n", (what_time() - philo.stamp), philo.rank + 1);
	pthread_mutex_lock(&philo.mutexes->next->mutex);
	printf("%lu %d has taken a right fork\n",(what_time() - philo.stamp), philo.rank + 1) ;
	printf("%lu %d is eating\n",(what_time() - philo.stamp), philo.rank + 1);
	usleep(philo.eat * 1000);
	philo.stamp_u = what_time();
	pthread_mutex_unlock(&philo.mutexes->mutex);
	pthread_mutex_unlock(&philo.mutexes->next->mutex);

}
void	*routine(void *phil)
{
	t_philos *philo;

	philo = (t_philos*)(phil);
	if ((philo[0].rank % 2) != 0)
		usleep(100);
	if (philo[0].eating == 0)
		return NULL;
	else if (philo[0].eating == -1)
		while (1)
		{
			eating(philo[0]);
			sleeping(philo[0]);
			thinking(philo[0]);
		}
	else if (philo[0].eating > 0)
		while (philo[0].eating)
		{
			eating(philo[0]);
			sleeping(philo[0]);
			thinking(philo[0]);
			philo[0].eating--;
		}
		return NULL;
}
void	*watcher_g(void	*phil)
{
	t_philos *philos;
	int i;

	i = 0;
	philos = phil;
	while (i < philos[0].n_ph)
	{
		printf("rank %d \n", philos[i].rank + 1);
		i++;
	}
	return NULL;

}
void	philosophers(t_philos *philo)
{
	int i;
	pthread_t	watcher;

	i = 0;
	// while (i < philo[0].n_ph)
	// {

	// 	pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
	// 	i++;
	// }
	pthread_create(&watcher, NULL, &watcher_g, philo);
	// i = 0;
	// while (i < philo[0].n_ph)
	// {
	// 	pthread_join(philo[i].thread,NULL);
	// 	i++;
	// }
	pthread_join(watcher, NULL);
}
