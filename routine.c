/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:16:00 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/12 11:54:15 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	even_eat_sleep(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->right_fork);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(philo->left_fork);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleep(philo->info->time_to_eat, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	timer_mutex(philo, &time);
	philo->last_meal = time;
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleep(philo->info->time_to_sleep, philo);
}

void	odd_eat_sleep(t_philo *philo, size_t time)
{
	ft_sleep(1, philo);
	pthread_mutex_lock(philo->left_fork);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(philo->right_fork);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	timer_mutex(philo, &time);
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleep(philo->info->time_to_eat, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	timer_mutex(philo, &time);
	philo->last_meal = time;
	pthread_mutex_lock(&philo->info->print);
	printf("%zu %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	ft_sleep(philo->info->time_to_sleep, philo);
}

int	loop_conditon(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->endflag);
	if (philo->info->dead_or_finished)
		return (pthread_mutex_unlock(&philo->info->endflag), 1);
	else
		return (pthread_mutex_unlock(&philo->info->endflag), 0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = arg;
	while (!loop_conditon(philo))
	{
		pthread_mutex_lock(&philo->info->time);
		pthread_mutex_unlock(&philo->info->time);
		if (philo->id % 2 == 0)
			even_eat_sleep(philo, time);
		pthread_mutex_lock(&philo->info->print);
		timer_mutex(philo, &time);
		printf("%zu %d is thinking\n", time, philo->id);
		pthread_mutex_unlock(&philo->info->print);
		if (philo->id % 2 != 0)
			odd_eat_sleep(philo, time);
	}
	return (0);
}
