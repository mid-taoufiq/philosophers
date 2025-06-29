/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/29 13:52:09 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	action_printer(size_t id, t_all *all, char *action)
{
	sem_wait(all->info.print);
	printf("%zu %ld %s\n", timer(0), id, action);
	sem_post(all->info.print);
}

void	philo_take(size_t id, t_all *all)
{
	sem_wait(all->info.forks);
	action_printer(id, all, "has taken a fork");
	sem_wait(all->info.forks);
	action_printer(id, all, "has taken a fork");
}

void	philo_eat(size_t id, t_all *all)
{
	if (!check_dead_fin(all))
		action_printer(id, all, "is eating");
	sem_wait(all->info.meal_time);
	all->philos[id - 1].last_meal = timer(0);
	sem_post(all->info.meal_time);
	ft_sleep(all->info.time_to_eat, all);
	sem_post(all->info.forks);
	sem_post(all->info.forks);
	all->philos[id - 1].meals_eaten++;
}

void	philo_sleep(size_t id, t_all *all)
{
	if (!check_dead_fin(all))
		action_printer(id, all, "is sleeping");
	ft_sleep(all->info.time_to_sleep, all);
}

bool	check_dead_fin(t_all *all)
{
	sem_wait(all->info.endflag);
	if (!all->info.dead_or_finished)
	{
		sem_post(all->info.endflag);
		return (false);
	}
	sem_post(all->info.endflag);
	return (true);
}
