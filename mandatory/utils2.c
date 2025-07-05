/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/05 17:47:22 by tibarike         ###   ########.fr       */
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

void	destroy_forks(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < all->info.philos_number)
	{
		pthread_mutex_destroy(&all->info.forks[i]);
		i++;
	}
}

void	destroy_remainings(t_all *all)
{
	destroy_forks(all);
	pthread_mutex_destroy(&all->info.meals_mutex);
	pthread_mutex_destroy(&all->info.print);
	pthread_mutex_destroy(&all->info.endflag);
}
