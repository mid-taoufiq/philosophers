/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:42:26 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/05 18:10:46 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	init_philo(t_philo *philo, t_all *all, size_t i)
{
	philo->id = i + 1;
	philo->finished = false;
	philo->info = &all->info;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
}

static void	post_remainings(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->philos_number)
	{
		if (sem_post(philo->info->wait_finished) != 0)
			break ;
		i++;
	}
}

static void	dead_part(t_philo *philo)
{
	size_t	flag;

	sem_wait(philo->info->meal_time);
	flag = timer(0) - philo->last_meal;
	sem_post(philo->info->meal_time);
	if (flag > philo->info->time_to_die)
	{
		sem_wait(philo->info->print);
		printf("%zu %d died\n", timer(0), philo->id);
		post_remainings(philo);
		free(philo->info->pid);
		close_sems(philo->info);
		exit(0);
	}
}

static void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		usleep(500);
		dead_part(philo);
	}
	return (NULL);
}

void	routine(t_all *all, size_t i)
{
	pthread_t	monitor;
	t_philo		philo;

	init_philo(&philo, all, i);
	if (pthread_create(&monitor, NULL, monitoring, &philo) == -1)
		return ;
	pthread_detach(monitor);
	if (philo.id % 2 != 0)
		usleep(500);
	while (1)
	{
		philo_take(philo.id, all);
		philo_eat(philo.id, all, &philo);
		philo_sleep(philo.id, all);
		action_printer(philo.id, all, "is thinking");
		if (all->info.times_philo_must_eat > 0
			&& philo.meals_eaten >= all->info.times_philo_must_eat)
		{
			if (!philo.finished)
			{
				philo.finished = true;
				sem_post(all->info.wait_finished);
			}
		}
	}
}
