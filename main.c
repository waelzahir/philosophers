/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:19:56 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/04 22:54:04 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	connect_mutexes(t_philos *philos, int n)
{
	int i;

	i = 1;
	while (i < n - 1)
	{
		philos[i].right_f = &philos[i + 1].left_f;
		i++;
	}
	philos[0].right_f = &philos[n - 1].left_f;
	philos[n - 1].right_f = &philos[0].left_f;

}
int init_mutexes(t_philos *philos)
{
	int i;

	i = 0;
	while (i < philos[0].n_ph)
	{
		if (pthread_mutex_init(&philos[i].left_f, NULL) == -1)
			return (philos[i].rank);
		i++;
	}
	connect_mutexes(philos, philos[0].n_ph);
	i = 0;
	while (i < philos[0].n_ph)
	{
		printf("philo %d , left fork %p \n", philos[i].rank , &philos[i].left_f);
		i++;
	}
	printf("\n\n\n");
	i = 0;
	while (i <philos[0].n_ph)
	{
		printf("philo %d , right fork %p \n", philos[i].rank , philos[i].right_f);
		i++;
	}
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
		philos[i].rank = i + 1;
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
			return (free(philos), 0);
		if (init_data(philos, av + 1) == 0)
			return (free(philos), 0);
	}
	else
		{
			printf("usage: ./philo n_of_ph t_to_die t_to_eat t_to_sleep [t_each_ph_eats]\n");
			printf("	[t_each_ph_eats] is optional\n");
		}
}

