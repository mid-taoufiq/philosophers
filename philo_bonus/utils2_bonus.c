/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/07 14:57:40 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	action_printer(size_t id, t_info *info, char *action)
{
	sem_wait(info->turn);
	sem_wait(info->print);
	printf("%zu %ld %s\n", timer(0), id, action);
	sem_post(info->print);
	sem_post(info->turn);
}

void	philo_take(size_t id, t_info *info)
{
	sem_wait(info->forks);
	action_printer(id, info, "has taken a fork");
	sem_wait(info->forks);
	action_printer(id, info, "has taken a fork");
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
