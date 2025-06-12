/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:18:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/12 17:49:55 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitoring(void *arg)
{
	size_t	i;
	size_t	flag;
	size_t	current_time;
	t_all	*all;

	all = arg;
	while (1)
	{
		pthread_mutex_lock(&all->info.i);
		i = 0;
		while (i < all->info.philos_number)
		{
			pthread_mutex_lock(&all->info.time);
			current_time = timer(0);
			pthread_mutex_unlock(&all->info.time);
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
				pthread_mutex_unlock(&all->info.i);
				return (0);
			}
			i++;
		}
		pthread_mutex_unlock(&all->info.i);
	}
	return (0);
}
