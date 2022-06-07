/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:42:04 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/07 18:14:55 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mutexes_destroy(t_philos *philos, int rank)
{
	int i;

	i = 0;
	if (!rank)
		return (0);
	while (i < rank)
	{
		pthread_mutex_destroy(&philos[i].mutexes->mutex);
		i++;
	}
	return (1);
}
