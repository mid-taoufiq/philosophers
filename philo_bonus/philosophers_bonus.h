/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/08 17:07:27 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_info
{
	size_t	philos_number;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_philo_must_eat;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*meal_time;
	sem_t	*wait_finished;
	sem_t	*turn;
}	t_info;

typedef struct s_philo
{
	int		id;
	size_t	meals_eaten;
	int		finished;
	size_t	last_meal;
	t_info	*info;
}	t_philo;

int		ft_atoi(char *nb, int *success);
void	usage_error(void);
int		check_number(char *str);
size_t	timer(int start);
void	ft_sleep(size_t time);
void	ft_putstr_fd(char *s, int fd);
void	action_printer(size_t id, t_info *info, char *action);
void	philo_take(size_t id, t_info *info);
void	philo_eat(size_t id, t_info *info, t_philo *philo);
void	philo_sleep(size_t id, t_info *info);
void	routine(t_info *info, size_t i);
void	close_sems(t_info *info);
void	create_children(t_info *info);
bool	check_meals(t_philo	*philo);
bool	check_finished(t_philo	*philo);
void	fork_fail(t_info *info, size_t i);

#endif