/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:42:26 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/29 13:54:27 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	dead_part(t_philo *philo)
{
	size_t	current_time;
	size_t	flag;

	current_time = timer(0);
	sem_wait(philo->info->meal_time);
	flag = current_time - philo->last_meal;
	sem_post(philo->info->meal_time);
	if (flag > philo->info->time_to_die)
	{
		sem_wait(philo->info->meal_time);
		philo->info->dead_or_finished = 1;
		sem_post(philo->info->meal_time);
		sem_wait(philo->info->print);
		printf("%zu %d died\n", current_time, philo->id);
		exit(0);
	}
}

static void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		dead_part(philo);
		usleep(1000);
	}
	return (NULL);
}

void	routine(t_all *all, size_t i)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitoring, &all->philos[i]) == -1)
		return ;
	pthread_detach(monitor);
	if (all->philos[i].id % 2 == 0)
		usleep(300);
	while (!check_dead_fin(all))
	{
		if (!check_dead_fin(all))
			action_printer(i + 1, all, "is thinking");
		philo_take(i + 1, all);
		philo_eat(i + 1, all);
		philo_sleep(i + 1, all);
		if (all->info.times_philo_must_eat > 0 &&
			all->philos[i].meals_eaten >= all->info.times_philo_must_eat)
		{
			if (!all->philos[i].finished)
			{
				all->philos[i].finished = true;
				sem_post(all->info.wait);
			}
		}
	}
}
