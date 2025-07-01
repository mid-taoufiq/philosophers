/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/01 20:47:49 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_children(t_all *all)
{
	size_t	i;

	i = 0;
	all->info.pid = malloc(sizeof(pid_t) * all->info.philos_number);
	if (!all->info.pid)
		return (-1);
	i = 0;
	while (i < all->info.philos_number)
	{
		all->info.pid[i] = fork();
		if (all->info.pid[i] == 0)
		{
			routine(all, i);
			exit(0);
		}
		else if (all->info.pid[i] < 0)
		{
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
}

void	sems_create(t_all *all)
{
	all->info.forks = sem_open("/forks", O_CREAT,
			0644, all->info.philos_number);
	if (all->info.forks == SEM_FAILED)
		(sem_unlink("/forks"), sem_close(all->info.forks), exit(1));
	all->info.print = sem_open("/print", O_CREAT, 0644, 1);
	if (all->info.print == SEM_FAILED)
		(sem_unlink("/print"), sem_close(all->info.print), exit(1));
	all->info.meal_time = sem_open("/meal_time", O_CREAT, 0644, 1);
	if (all->info.meal_time == SEM_FAILED)
		(sem_unlink("/meal_time"), sem_close(all->info.meal_time), exit(1));
	all->info.wait_finished = sem_open("/wait_finished", O_CREAT, 0644, 1);
	if (all->info.wait_finished == SEM_FAILED)
		(sem_unlink("/wait_finished"),
			sem_close(all->info.wait_finished), exit(1));
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal_time");
	sem_unlink("/endflag");
	sem_unlink("/wait_finished");
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
