/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/30 17:09:55 by tibarike         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_info
{
	int		dead_or_finished;
	size_t	philos_number;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_philo_must_eat;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*meal_time;
	sem_t	*endflag;
	sem_t	*wait_finished;
}	t_info;

typedef struct s_philo
{
	int		id;
	size_t	meals_eaten;
	size_t	last_meal;
	bool	finished;
	t_info	*info;
}	t_philo;

typedef struct s_all
{
	t_info	info;
	t_philo	*philos;
}	t_all;

int		ft_atoi(char *nb, int *success);
void	usage_error(void);
int		check_number(char *str);
size_t	timer(int start);
void	ft_sleep(size_t time, t_all *all);
void	ft_putstr_fd(char *s, int fd);
bool	check_dead_fin(t_all *all);
void	action_printer(size_t id, t_all *all, char *action);
void	philo_take(size_t philon, t_all *all);
void	philo_eat(size_t philon, t_all *all);
void	philo_sleep(size_t philon, t_all *all);
void	routine(t_all *all, size_t i);
void	sems_create(t_all *all);
void	close_sems(t_all *all);
int		create_children(t_all *all);

#endif