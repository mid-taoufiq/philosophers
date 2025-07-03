/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:16:00 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/03 17:48:35 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	dead_fin_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->endflag);
	if (philo->info->dead_or_finished == 1)
	{
		pthread_mutex_unlock(&philo->info->endflag);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->endflag);
	return (false);
}

static bool	even_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (dead_fin_condition(philo))
		return (pthread_mutex_unlock(philo->left_fork), false);
	action_printer("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->right_fork);
	if (dead_fin_condition(philo))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), false);
	action_printer("has taken a fork", philo->id, philo);
	action_printer("is eating", philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = timer(0);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	action_printer("is sleeping", philo->id, philo);
	ft_sleep(philo->info->time_to_sleep, philo);
	action_printer("is thinking", philo->id, philo);
	return (true);
}

static bool	odd_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (dead_fin_condition(philo))
		return (pthread_mutex_unlock(philo->right_fork), false);
	action_printer("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->left_fork);
	if (dead_fin_condition(philo))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), false);
	action_printer("has taken a fork", philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = timer(0);
	action_printer("is eating", philo->id, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	action_printer("is sleeping", philo->id, philo);
	ft_sleep(philo->info->time_to_sleep, philo);
	action_printer("is thinking", philo->id, philo);
	return (true);
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
	if (philo->id % 2 != 0)
	{
		action_printer("is thinking", philo->id, philo);
		usleep(500);
	}
	else
		action_printer("is thinking", philo->id, philo);
	while (!dead_fin_conditon(philo))
	{
		if (philo->id % 2 == 0)
		{
			if (!even_eat_sleep(philo))
				return ;
		}
		if (philo->id % 2 != 0)
		{
			if (!odd_eat_sleep(philo))
				return ;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->info->philos_number == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		action_printer("has taken a fork", philo->id, philo);
		ft_sleep(philo->info->time_to_die, philo);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	two_plus(philo);
	return (0);
}
