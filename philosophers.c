/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/06 20:57:30 by ozahir           ###   ########.fr       */
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
	pthread_mutex_lock(philo.right_f);
	printf("%d has taken a fork\n", philo.rank);
	pthread_mutex_lock(&philo.left_f);
	printf("%d has taken a fork\n", philo.rank);
	usleep(philo.eat * 1000);
	pthread_mutex_unlock(philo.right_f);
	pthread_mutex_unlock(&philo.left_f);

}
void	*routine(t_philos philo)
{
	if (philo.eating == 0)
		return NULL;
	else if (philo.eating == -1)
		while (1)
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	else if (philo.eating > 0)
		while (philo.eating)
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
			philo.eating--;
		}
		return NULL;
}
void	philosophers(t_philos *philo)
{
	int i;

	i = 0;
	while (i < philo[0].n_ph)
	{
		pthread_create(philo[i].thread, NULL, routine(philo[i]) ,NULL);
		i++;
	}
	printf ("ff");
	i = 0;
	while (i < philo[0].n_ph)
	{
		pthread_join(*philo[i].thread,NULL);
		i++;
	}
}
