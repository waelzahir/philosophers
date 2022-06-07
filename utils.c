/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:07:50 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/07 21:10:05 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
static	int	my_isspace(int c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	j;
	long	count;

	i = 0;
	j = 1;
	count = 0;
	while (my_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		j *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	else if (str[i] <= '0' && str[i] >= '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = (str[i] - 48) + (count * 10);
		i++;
	}
	return (count * j);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	what_time()
{
	struct timeval tv;

	gettimeofday(&tv , NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
