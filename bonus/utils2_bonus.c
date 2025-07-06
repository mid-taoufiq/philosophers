/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/05 17:42:56 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	action_printer(size_t id, t_philo *philo, char *action)
{
	sem_wait(philo->info->print);
	if (philo->finished == false)
		printf("%zu %ld %s\n", timer(0), id, action);
	sem_post(philo->info->print);
}

void	philo_take(size_t id, t_philo *philo)
{
	sem_wait(philo->info->turn);
	sem_wait(philo->info->forks);
	action_printer(id, philo, "has taken a fork");
	sem_wait(philo->info->forks);
	action_printer(id, philo, "has taken a fork");
	sem_post(philo->info->turn);
}

void	philo_eat(size_t id, t_philo *philo)
{
	sem_wait(philo->info->meal_time);
	philo->last_meal = timer(0);
	sem_post(philo->info->meal_time);
	philo->meals_eaten++;
	action_printer(id, philo, "is eating");
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	ft_sleep(philo->info->time_to_eat);
}

void	philo_sleep(size_t id, t_philo *philo)
{
	action_printer(id, philo, "is sleeping");
	ft_sleep(philo->info->time_to_sleep);
}
