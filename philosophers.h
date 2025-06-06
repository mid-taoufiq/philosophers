/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/04 10:43:14 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_info
{
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_philos_eat;
	int				is_dead;
	int				is_finished;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_all
{
	t_info	data;
	t_philo	*philos;
}	t_all;

int		ft_atoi(char *nb, int *success);
void	usage_error(void);
int		check_number(char *str);

#endif