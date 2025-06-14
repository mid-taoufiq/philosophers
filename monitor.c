/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:18:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/14 09:57:40 by tibarike         ###   ########.fr       */
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
			i++;
		}
	}
	return (0);
}
