/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/14 12:03:58 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
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
	size_t			number_of_times_philos_eat;
	pthread_mutex_t	i;
	pthread_mutex_t	print;
	pthread_mutex_t	endflag;
	pthread_mutex_t	time;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}	t_philo;

typedef struct s_all
{
	t_info	info;
	t_philo	*philos;
}	t_all;

long	ft_atol(char *nb, int *success);
void	usage_error(void);
int		check_number(char *str);
void	*routine(void *arg);
size_t	timer(int start);
void	timer_mutex(t_philo *philo, size_t *time);
void	ft_sleep(size_t time);
int		dead_fin_conditon(t_philo *philo);
void	*monitoring(void *arg);
void	action_printer(int option, size_t time, int id, t_philo *philo);
void	unlock_mutexes(t_philo *philo);

#endif