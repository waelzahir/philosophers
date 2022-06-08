/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/08 17:20:08 by ozahir           ###   ########.fr       */
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
void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutexes->mutex);
	printf("%lu %d has taken a left fork\n", (what_time() - philo->stamp), philo->rank + 1);
	pthread_mutex_lock(&philo->mutexes->next->mutex);
	printf("%lu %d has taken a right fork\n",(what_time() - philo->stamp), philo->rank + 1) ;
	printf("%lu %d is eating\n",(what_time() - philo->stamp), philo->rank + 1);
	usleep(philo->eat * 1000);
	pthread_mutex_unlock(&philo->mutexes->mutex);
	pthread_mutex_unlock(&philo->mutexes->next->mutex);
	philo->stamp_u = what_time();


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
			eating(&philo[0]);
			sleeping(philo[0]);
			thinking(philo[0]);
		}
	else if (philo[0].eating > 0)
		while (philo[0].eating)
		{
			eating(&philo[0]);
			sleeping(philo[0]);
			thinking(philo[0]);
			philo[0].eating--;
		}
		return NULL;
}
void lock_forks(t_mutexes *mutexes, int len)
{
	int i = 0;

	while (i < len)
	{
		pthread_mutex_unlock(&mutexes->mutex);
		pthread_mutex_lock(&mutexes->mutex);
		mutexes = mutexes->next;
		i++;
	}
}
void	*watcher_g(void	*phil)
{
	t_philos *philos;
	int i;
	int *num;

	num = malloc(sizeof(int));
	i = 0;
	philos = phil;
	while (i < philos[0].n_ph)
	{
		if (philos[i].death < (what_time() - philos[i].stamp_u) )
		{
			*num  = i;
			return ((void* ) num);
		}
		i++;
		usleep(10);
		if (i == (philos[0].n_ph))
		 i = 0;
	}
	return NULL;

}
int	philosophers(t_philos *philo)
{
	int i;
	int *num;
	pthread_t	watcher;

	i = 0;
	while (i < philo[0].n_ph)
	{

		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	pthread_create(&watcher, NULL, &watcher_g, philo);
	pthread_join(watcher, (void **) &num);
	return *num;
	i = 0;
	while (i < philo[0].n_ph)
	{
		pthread_join(philo[i].thread,NULL);
		i++;
	}

	return -1;
}
