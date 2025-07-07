/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:42:26 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/07 15:32:27 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	init_philo(t_philo *philo, t_info *info, size_t i)
{
	philo->id = i + 1;
	philo->info = info;
	philo->finished = 0;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
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
		sem_wait(philo->info->meal_time);
		philo->info->dead_or_finished = 1;
		sem_post(philo->info->meal_time);
		exit(1);
	}
}

static void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		usleep(1000);
		dead_part(philo);
		if (philo->info->times_philo_must_eat > 0 && check_meals(philo))
		{
			sem_wait(philo->info->wait_finished);
			philo->finished = 1;
			sem_post(philo->info->wait_finished);
		}
	}
	return (NULL);
}

void	routine(t_info *info, size_t i)
{
	pthread_t	monitor;
	t_philo		philo;

	free(info->pid);
	init_philo(&philo, info, i);
	if (pthread_create(&monitor, NULL, monitoring, &philo) == -1)
		return ;
	pthread_detach(monitor);
	if (philo.id % 2 != 0)
		usleep(500);
	while (1)
	{
		philo_take(philo.id, info);
		philo_eat(philo.id, info, &philo);
		philo_sleep(philo.id, info);
		action_printer(philo.id, info, "is thinking");
		if (philo.finished)
			exit(0);
	}
	exit(0);
}
