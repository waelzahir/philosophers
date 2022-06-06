/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:42:04 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/05 17:50:21 by ozahir           ###   ########.fr       */
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
		pthread_mutex_destroy(&philos[i].left_f);
		i++;
	}
	return (1);
}
