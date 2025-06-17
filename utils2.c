/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/14 13:57:19 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
