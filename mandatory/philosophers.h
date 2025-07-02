/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/02 19:03:58 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info
{
	int				dead_or_finished;
	size_t			philos_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			times_philo_must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	endflag;
	pthread_mutex_t	time;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				finished;
	size_t			meals_eaten;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}	t_philo;

typedef struct s_all
{
	t_info	info;
	t_philo	*philos;
}	t_all;

int		ft_atoi(char *nb, int *success);
void	usage_error(void);
int		check_number(char *str);
void	*routine(void *arg);
size_t	timer(int start);
void	ft_sleep(size_t time, t_philo *philo);
void	*monitoring(void *arg);
void	action_printer(char *action, int id, t_philo *philo);
int		mutex_init(t_all *all);
void	unlock_mutexes(t_philo *philo);

#endif