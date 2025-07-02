/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:16:00 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/02 14:02:41 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	even_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	action_printer("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->left_fork);
	action_printer("has taken a fork", philo->id, philo);
	action_printer("is eating", philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = timer(0);
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	unlock_mutexes(philo);
	action_printer("is sleeping", philo->id, philo);
	ft_sleep(philo->info->time_to_sleep, philo);
}

static void	odd_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	action_printer("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->right_fork);
	action_printer("has taken a fork", philo->id, philo);
	action_printer("is eating", philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = timer(0);
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	unlock_mutexes(philo);
	action_printer("is sleeping", philo->id, philo);
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

void	two_plus(t_philo *philo)
{
	action_printer("is thinking", philo->id, philo);
	if (philo->id % 2 == 0)
		even_eat_sleep(philo);
	if (philo->id % 2 != 0)
		odd_eat_sleep(philo);
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
			action_printer("is thinking", philo->id, philo);
			action_printer("has taken a fork", philo->id, philo);
			ft_sleep(philo->info->time_to_die, philo);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		two_plus(philo);
	}
	return (0);
}
