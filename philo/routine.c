/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:52:18 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/08 14:15:34 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	action_printer(char *action, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	if (!check_dead_fin(philo))
		printf("%zu %d %s\n", timer(0), id, action);
	pthread_mutex_unlock(&philo->info->print);
}

static bool	case_one(t_philo *philo)
{
	if (philo->info->philos_number == 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
		action_printer("has taken a fork", philo->id, philo);
		pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
		ft_sleep(philo->info->time_to_die, philo);
		return (true);
	}
	return (false);
}

static void	take_eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->info->turn);
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	action_printer("has taken a left fork", philo->id, philo);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	action_printer("has taken a right fork", philo->id, philo);
	// pthread_mutex_unlock(&philo->info->turn);
	//-----------
	action_printer("is eating", philo->id, philo);
	pthread_mutex_lock(&philo->info->meals_mutex);
	philo->last_meal = timer(0);
	philo->meals_eaten++;//alasir
	pthread_mutex_unlock(&philo->info->meals_mutex);
	ft_sleep(philo->info->time_to_eat, philo);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (case_one(philo))
		return (0);
	action_printer("is thinking", philo->id, philo);
	if (philo->info->philos_number > 40)
	{
		if (philo->id % 2 != 0)
			ft_sleep(philo->info->time_to_eat, philo);
	}
	else
	{
		if (philo->id % 2 != 0)
			usleep(500);
	}
	while (!check_dead_fin(philo))
	{
		take_eat(philo);
		unlock_forks(philo);
		if (check_philo_finished(philo))
			return (0);
		action_printer("is sleeping", philo->id, philo);
		ft_sleep(philo->info->time_to_sleep, philo);
		action_printer("is thinking", philo->id, philo);
	}
	return (0);
}
