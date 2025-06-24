/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/18 15:12:29 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_init(t_all *all)
{
	if (pthread_mutex_init(&all->info.print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->info.endflag, NULL) != 0)
		return (pthread_mutex_destroy(&all->info.print), 1);
	if (pthread_mutex_init(&all->info.meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&all->info.print);
		pthread_mutex_destroy(&all->info.endflag);
		return (1);
	}
	if (pthread_mutex_init(&all->info.time, NULL) != 0)
	{
		pthread_mutex_destroy(&all->info.print);
		pthread_mutex_destroy(&all->info.endflag);
		pthread_mutex_destroy(&all->info.meals_mutex);
		return (1);
	}
	return (0);
}

void	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	timer_mutex(t_philo *philo, size_t *time)
{
	pthread_mutex_lock(&philo->info->time);
	*time = timer(0);
	pthread_mutex_unlock(&philo->info->time);
}

void	action_printer(int option, size_t *time, int id, t_philo *philo)
{
	timer_mutex(philo, time);
	pthread_mutex_lock(&philo->info->endflag);
	if (option == 1 && !philo->info->dead_or_finished)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%zu %d has taken a fork\n", *time, id);
		pthread_mutex_unlock(&philo->info->print);
	}
	else if (option == 2 && !philo->info->dead_or_finished)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%zu %d is eating\n", *time, id);
		pthread_mutex_unlock(&philo->info->print);
	}
	else if (option == 3 && !philo->info->dead_or_finished)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%zu %d is sleeping\n", *time, id);
		pthread_mutex_unlock(&philo->info->print);
	}
	pthread_mutex_unlock(&philo->info->endflag);
}
