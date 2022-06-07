/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:19:56 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/07 21:28:54 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_mutexes(t_philos *philos)
{
	int i;
	t_mutexes *mutexes;

	mutexes = malloc(sizeof(t_mutexes));
	if (!mutexes)
		return (philos[0].rank);
	i = 0;
	while (i < philos[0].n_ph)
	{
		philos[i].mutexes = mutexes;

		if (pthread_mutex_init(&mutexes->mutex, NULL) == -1)
			return (philos[i].rank);
		if ((i + 1) == philos[0].n_ph)
			break ;
		mutexes->next = malloc(sizeof(t_mutexes));
		mutexes = mutexes->next;
		i++;
	}
	mutexes->next = philos[0].mutexes;
	return (0);
}

int init_data(t_philos *philos, char	**args)
{
	int	n_ph;
	int i;

	i = 0;
	n_ph = ft_atoi(args[0]);
	if (n_ph == 0)
		return (0);
	while(i < n_ph)
	{
		philos[i].n_ph  = n_ph;
		philos[i].stamp = what_time();
		philos[i].stamp_u = what_time();
		philos[i].rank = i;
		philos[i].death = ft_atoi(args[1]);
		philos[i].eat =ft_atoi(args[2]);
		philos[i].sleep = ft_atoi(args[3]);
		if (args[4] == NULL)
			philos[i].eating = -1;
		else
			philos[i].eating = ft_atoi(args[4]);
		i++;
	}
	init_mutexes(philos);
	// if (mutexes_destroy(philos, init_mutexes(philos)))
	// 	return (0);
	return 1;
}
int main(int	ac, char	**av)
{
	t_philos	*philos;

	if (ac >= 5 && ac <= 6)
	{
		if (ft_atoi(av[1]) <= 0)
			return (printf("the subject requires more than one phil\n"), 0);
		if (input_eval(av + 1) == 0)
			return (0);
		philos = malloc((ft_atoi(av[1])) * sizeof(t_philos));
		if (!philos)
			return (0);
		if (init_data(philos, av + 1) == 0)
			return (free(philos), 0);

			philosophers(philos);
	}
	else
		{
			printf("usage: ./philo n_of_ph t_to_die t_to_eat t_to_sleep [t_each_ph_eats]\n");
			printf("	[t_each_ph_eats] is optional\n");
		}
}

