/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/01 20:47:57 by tibarike         ###   ########.fr       */
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

void	philo_eat(size_t id, t_all *all, t_philo *philo)
{
	action_printer(id, all, "is eating");
	sem_wait(all->info.meal_time);
	philo->last_meal = timer(0);
	sem_post(all->info.meal_time);
	ft_sleep(all->info.time_to_eat);
	sem_post(all->info.forks);
	sem_post(all->info.forks);
	philo->meals_eaten++;
}

void	philo_sleep(size_t id, t_all *all)
{
	action_printer(id, all, "is sleeping");
	ft_sleep(all->info.time_to_sleep);
}
