/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/04 16:47:59 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead_fin(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->endflag);
	if (philo->info->dead_or_finished == 1)
	{
		pthread_mutex_unlock(&philo->info->endflag);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->endflag);
	return (0);
}

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
	return (0);
}
