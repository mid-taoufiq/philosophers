/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/07 15:32:19 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	check_meals(t_philo	*philo)
{
	size_t	meals;

	sem_wait(philo->info->meal_time);
	meals = philo->meals_eaten;
	sem_post(philo->info->meal_time);
	if (meals == philo->info->times_philo_must_eat)
		return (true);
	return (false);
}

bool	check_finished(t_philo	*philo)
{
	bool	finished;

	sem_wait(philo->info->wait_finished);
	finished = philo->finished;
	sem_post(philo->info->wait_finished);
	return (finished);
}

int	create_children(t_info *info)
{
	size_t	i;

	i = 0;
	info->pid = malloc(sizeof(pid_t) * info->philos_number);
	if (!info->pid)
		return (-1);
	i = 0;
	while (i < info->philos_number)
	{
		info->pid[i] = fork();
		if (info->pid[i] == 0)
		{
			routine(info, i);
			exit(0);
		}
		else if (info->pid[i] < 0)
		{
			free(info->pid);
			ft_putstr_fd("fork failed", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	close_sems(t_info *info)
{
	sem_close(info->forks);
	sem_close(info->print);
	sem_close(info->meal_time);
	sem_close(info->wait_finished);
	sem_close(info->turn);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
