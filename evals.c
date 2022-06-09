/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:27:36 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 15:51:46 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_num(char	*number)
{
	int	i;
	int	len;

	len = ft_strlen(number);
	i = 0;
	if (len == 1 && number[0] == '0')
		return (0);
	while (i < len)
	{
		if (number[i] == '+' || (number[i] <= '9' && number[i] >= '0'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_right(char *number)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (number[i])
	{
		if (number[i] == '+')
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	else if (j == 1 && number[0] == '+')
		return (1);
	return (0);
}

int	input_eval(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_num(av[i]) == 0)
			return (0);
		if (is_right(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
