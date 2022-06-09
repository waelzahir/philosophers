/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:46:40 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 22:52:54 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char	**av)
{

	if (ac >= 5 && ac <= 6)
	{
		if (ft_atoi(av[1]) <= 0)
			return (printf("the subject requires more than one phil\n"), 0);
		if (input_eval(av + 1) == 0)
			return (printf("invalid arguments\n"), 0);

	}
	else
	{
		printf("usage: ./philo philos death eat sleep [t_each_p_eats]\n");
		printf("	[t_each_ph_eats] is optional\n");
	}


}
