/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/09 18:07:48 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	fork_fail(t_info *info, size_t i)
{
	size_t	j;
	int		status;

	j = 0;
	status = 0;
	free(info->pid);
	ft_putstr_fd("fork failed\n", 2);
	while (j < i)
	{
		kill(info->pid[j], SIGKILL);
		j++;
	}
	while (waitpid(-1, &status, 0) == 0)
		continue ;
	close_sems(info);
	free(info->pid);
	exit(1);
}

void	action_printer(size_t id, t_info *info, char *action)
{
	sem_wait(info->print);
	printf("%zu %ld %s\n", timer(0), id, action);
	sem_post(info->print);
}

void	philo_take(size_t id, t_info *info)
{
	sem_wait(info->turn);
	sem_wait(info->forks);
	action_printer(id, info, "has taken a fork");
	sem_wait(info->forks);
	action_printer(id, info, "has taken a fork");
	sem_post(info->turn);
}

void	philo_eat(size_t id, t_info *info, t_philo *philo)
{
	action_printer(id, info, "is eating");
	sem_wait(info->meal_time);
	philo->last_meal = timer(0);
	sem_post(info->meal_time);
	ft_sleep(info->time_to_eat);
	sem_wait(info->meal_time);
	philo->meals_eaten++;
	sem_post(info->meal_time);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	philo_sleep(size_t id, t_info *info)
{
	action_printer(id, info, "is sleeping");
	ft_sleep(info->time_to_sleep);
}
