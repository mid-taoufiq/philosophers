/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:58:20 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/26 10:03:12 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_take(size_t philon, sem_t *forks, sem_t *print)
{
	sem_wait(forks);
	sem_wait(print);
	printf("%zu %ld has taken a fork\n", timer(0), philon + 1);
	sem_post(print);
	sem_wait(forks);
	sem_wait(print);
	printf("%zu %ld has taken a fork\n", timer(0), philon + 1);
	sem_post(print);
}

void	philo_eat(size_t philon, t_all *all, sem_t *forks, sem_t *print)
{
	size_t	time;

	time = timer(0);
	sem_wait(print);
	printf("%zu %ld is eating\n", time, philon + 1);
	sem_post(print);
	all->philos[philon].last_meal = time;
	ft_sleep(all->info.time_to_eat, all->info);
	sem_post(forks);
	sem_post(forks);
	all->philos[philon].meals_eaten++;
}

void	philo_sleep(size_t philon, t_all *all, sem_t *print)
{
	sem_wait(print);
	printf("%zu %ld is sleeping\n", timer(0), philon + 1);
	sem_post(print);
	ft_sleep(all->info.time_to_sleep, all->info);
}
