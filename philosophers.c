/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:24:23 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/05 19:19:56 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philos philo)
{
	printf("%dsleeping\n", philo.rank);
	usleep(philo.sleep * 1000);

}
void	thinking(t_philos philo)
{
	printf("%dis thinkinh\n", philo.rank);
	pthread_mutex_lock(philo.right_f);
	printf("%d has taken a fork\n", philo.rank);
	pthread_mutex_lock(&philo,left_f);
	printf("%d has taken a fork\n", philo.rank);

	eating

}
void	philosophers(t_philos *philos)
{


}
