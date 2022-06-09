/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:12:19 by ozahir            #+#    #+#             */
/*   Updated: 2022/06/09 17:06:49 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_mutexes
{
	pthread_mutex_t		mutex;
	pthread_mutex_t		print;
	int					i;
	struct s_mutexes	*next;
}	t_mutexes;

typedef struct s_philos
{
	pthread_t	thread;
	int			n_ph;
	long		stamp;
	long		stamp_u;
	int			rank;
	long		death;
	long		eat;
	long		sleep;
	int			eating;
	t_mutexes	*mutexes;
}	t_philos;

t_mutexes	*get_mutex(t_mutexes *mutexes);
int			input_eval(char **av);
void		free_data(t_philos *philos);
int			mutexes_destroy(t_philos *philos, int rank);
int			init_mutexes(t_philos *philos);
int			init_data(t_philos *philos, char **args);
void		sleeping(t_philos *philo);
void		thinking(t_philos *philo);
void		eating(t_philos *philo);
void		*routine(void *phil);
int			all_eaten(t_philos *philos);
void		*watcher_g(void	*phil);
int			philosophers(t_philos *philo);
int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
long		what_time(void);

#endif
