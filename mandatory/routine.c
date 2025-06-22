/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:16:00 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/18 15:11:40 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	even_eat_sleep(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->right_fork);
	action_printer(1, &time, philo->id, philo);
	pthread_mutex_lock(philo->left_fork);
	action_printer(1, &time, philo->id, philo);
	action_printer(2, &time, philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	unlock_mutexes(philo);
	action_printer(3, &time, philo->id, philo);
	ft_sleep(philo->info->time_to_sleep, philo);
}

static void	odd_eat_sleep(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->left_fork);
	action_printer(1, &time, philo->id, philo);
	pthread_mutex_lock(philo->right_fork);
	action_printer(1, &time, philo->id, philo);
	action_printer(2, &time, philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	unlock_mutexes(philo);
	action_printer(3, &time, philo->id, philo);
	ft_sleep(philo->info->time_to_sleep, philo);
}

static int	dead_fin_conditon(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->endflag);
	if (!philo->info->dead_or_finished)
	{
		pthread_mutex_unlock(&philo->info->endflag);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->endflag);
		return (1);
	}
}

void	two_plus(t_philo *philo, size_t *time)
{
	timer_mutex(philo, time);
	pthread_mutex_lock(&philo->info->endflag);
	if (!philo->info->dead_or_finished)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%zu %d is thinking\n", *time, philo->id);
		pthread_mutex_unlock(&philo->info->print);
	}
	pthread_mutex_unlock(&philo->info->endflag);
	if (philo->id % 2 == 0)
		even_eat_sleep(philo, *time);
	if (philo->id % 2 != 0)
		odd_eat_sleep(philo, *time);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = arg;
	time = 0;
	if (philo->id % 2 == 0)
		usleep(300);
	while (!dead_fin_conditon(philo))
	{
		if (philo->info->philos_number == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			action_printer(1, &time, philo->id, philo);
			ft_sleep(philo->info->time_to_die, philo);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		two_plus(philo, &time);
	}
	return (0);
}
