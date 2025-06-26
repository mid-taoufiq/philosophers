/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/26 14:38:32 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_take(size_t philon, t_all *all)
{
	sem_wait(all->info.forks);
	sem_wait(all->info.print);
	if (!all->info.dead_or_finished)
		printf("%zu %ld has taken a fork\n", timer(0), philon + 1);
	sem_post(all->info.print);
	sem_wait(all->info.forks);
	sem_wait(all->info.print);
	if (!all->info.dead_or_finished)
		printf("%zu %ld has taken a fork\n", timer(0), philon + 1);
	sem_post(all->info.print);
}

void	philo_eat(size_t philon, t_all *all)
{
	size_t	time;

	time = timer(0);
	sem_wait(all->info.print);
	if (!all->info.dead_or_finished)
		printf("%zu %ld is eating\n", time, philon + 1);
	sem_post(all->info.print);
	all->philos[philon].last_meal = time;
	ft_sleep(all->info.time_to_eat, all->info);
	sem_post(all->info.forks);
	sem_post(all->info.forks);
	all->philos[philon].meals_eaten++;
}

void	philo_sleep(size_t philon, t_all *all)
{
	sem_wait(all->info.print);
	if (all->info.dead_or_finished == 0)
		printf("%zu %ld is sleeping\n", timer(0), philon + 1);
	sem_post(all->info.print);
	ft_sleep(all->info.time_to_sleep, all->info);
}
