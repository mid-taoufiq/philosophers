/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:18:52 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/18 17:38:40 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_finished(t_all *all)
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

static bool	finished_part(t_all *all, size_t i)
{
	if (check_finished(all))
	{
		pthread_mutex_lock(&all->info.endflag);
		all->info.dead_or_finished = 1;
		pthread_mutex_unlock(&all->info.endflag);
		return (true);
	}
	pthread_mutex_lock(&all->info.meals_mutex);
	if (all->philos[i].meals_eaten == all->info.times_philo_must_eat)
		all->philos[i].finished = 1;
	pthread_mutex_unlock(&all->info.meals_mutex);
	return (false);
}

static bool	dead_part(t_all *all, size_t i)
{
	size_t	current_time;
	size_t	flag;

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
		return (true);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	size_t	i;
	t_all	*all;

	all = arg;
	while (1)
	{
		usleep(10);
		i = 0;
		while (i < all->info.philos_number)
		{
			if (dead_part(all, i))
				return (0);
			if (all->info.times_philo_must_eat > 0)
			{
				if (finished_part(all, i))
					return (0);
			}
			i++;
		}
	}
	return (0);
}
