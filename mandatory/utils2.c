/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/02 12:56:20 by tibarike         ###   ########.fr       */
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

void	action_printer(char *action, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->endflag);
	if (!philo->info->dead_or_finished)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%zu %d %s\n", timer(0), id, action);
		pthread_mutex_unlock(&philo->info->print);
	}
	pthread_mutex_unlock(&philo->info->endflag);
}
