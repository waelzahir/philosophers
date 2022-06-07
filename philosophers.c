/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/07 17:50:40 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philos philo)
{
	printf("%d sleeping\n", philo.rank);
	usleep(philo.sleep * 1000);
}
void	thinking(t_philos philo)
{
	printf("%d is thinking\n", philo.rank);
}
void	eating(t_philos philo)
{

	pthread_mutex_lock(&philo.mutexes->mutex);
	printf("%d has taken a left fork\n", philo.rank);
		pthread_mutex_lock(&philo.mutexes->next->mutex);
	printf("%d has taken a right  fork\n", philo.rank);
	printf("%d is eating\n", philo.rank);
	usleep(philo.eat * 1000);


	pthread_mutex_unlock(&philo.mutexes->mutex);
	printf("%d left unlocked\n", philo.rank);
		pthread_mutex_unlock(&philo.mutexes->next->mutex);
	printf("%d right unlocked\n", philo.rank);

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
void	philosophers(t_philos *philo)
{
	int i;

	i = 0;
	while (i < philo[0].n_ph)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo[0].n_ph)
	{
		pthread_join(philo[i].thread,NULL);
		i++;
	}
}
