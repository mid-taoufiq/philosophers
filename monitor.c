/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:18:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/18 14:59:36 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_finished(t_all *all)
{
	size_t	j;

	j = 0;
	while (j < all->info.philos_number)
	{
		if (all->philos[j].finished == 1)
			j++;
		else
			break ;
	}
	if (j == all->info.philos_number)
		return (true);
	else
		return (false);
}

void	*monitoring(void *arg)
{
	size_t	i;
	size_t	flag;
	size_t	current_time;
	t_all	*all;

	all = arg;
	while (1)
	{
		i = 0;
		while (i < all->info.philos_number)
		{
			current_time = timer(0);
			pthread_mutex_lock(&all->info.meals_mutex);
			flag = current_time - all->philos[i].last_meal;
			pthread_mutex_unlock(&all->info.meals_mutex);
			if (flag > all->info.time_to_die)
			{
				pthread_mutex_lock(&all->info.endflag);
				all->info.dead_or_finished = 1;
				pthread_mutex_unlock(&all->info.endflag);
				pthread_mutex_lock(&all->info.print);
				printf("%zu %lu died\n", current_time, i + 1);
				pthread_mutex_unlock(&all->info.print);
				return (0);
			}
			if (all->info.times_philo_must_eat > 0)
			{
				if (check_finished(all))
				{
					pthread_mutex_lock(&all->info.endflag);
					all->info.dead_or_finished = 1;
					pthread_mutex_unlock(&all->info.endflag);
					return (0);
				}
				pthread_mutex_lock(&all->info.meals_mutex);
				if (all->philos[i].meals_eaten == all->info.times_philo_must_eat)
					all->philos[i].finished = 1;
				pthread_mutex_unlock(&all->info.meals_mutex);
				
			}
			i++;
		}
	}
	return (0);
}
