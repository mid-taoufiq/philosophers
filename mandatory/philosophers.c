/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/02 20:40:29 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	join_free(t_philo *philos, t_info info)
{
	size_t	i;

	i = 0;
	while (i < info.philos_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info.philos_number)
	{
		pthread_mutex_destroy(&info.forks[i]);
		i++;
	}
	free(philos);
	free(info.forks);
}

static void	start_routine(t_all *all)
{
	size_t		i;
	pthread_t	monitor;

	i = 0;
	while (i < all->info.philos_number)
	{
		if (pthread_create(&all->philos[i].thread,
				NULL, routine, &all->philos[i]) == -1)
		{
			while ((int)--i >= 0)
				pthread_join(all->philos[i].thread, NULL);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, all) == -1)
		return (join_free(all->philos, all->info));
	pthread_join(monitor, NULL);
}

static void	philo_init(t_all *all)
{
	size_t		i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * (all->info.philos_number));
	if (!all->philos)
		return ;
	while (i < all->info.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].left_fork = &all->info.forks[i];
		all->philos[i].right_fork = &all->info.forks[
			(i + 1) % all->info.philos_number];
		all->philos[i].info = &all->info;
		all->philos[i].finished = 0;
		pthread_mutex_lock(&all->info.meals_mutex);
		all->philos[i].meals_eaten = 0;
		all->philos[i].last_meal = timer(0);
		pthread_mutex_unlock(&all->info.meals_mutex);
		i++;
	}
	start_routine(all);
	join_free(all->philos, all->info);
}

static int	data_init(t_all *all, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	all->info.philos_number = check_number(argv[1]);
	if (all->info.philos_number == 0)
		return (0);
	all->info.time_to_die = check_number(argv[2]);
	if (all->info.time_to_die == 0)
		return (0);
	all->info.time_to_eat = check_number(argv[3]);
	if (all->info.time_to_eat == 0)
		return (0);
	all->info.time_to_sleep = check_number(argv[4]);
	if (all->info.time_to_sleep == 0)
		return (0);
	if (argc == 6)
	{
		all->info.times_philo_must_eat = check_number(argv[5]);
		if (all->info.times_philo_must_eat == 0)
			return (0);
	}
	else
		all->info.times_philo_must_eat = 0;
	all->info.dead_or_finished = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_all		all;
	size_t		i;

	timer(1);
	i = 0;
	if (!data_init(&all, argc, argv))
		return (1);
	all.info.forks = malloc(all.info.philos_number * sizeof(pthread_mutex_t));
	if (!all.info.forks)
		return (1);
	while (i < all.info.philos_number)
	{
		if (pthread_mutex_init(&all.info.forks[i], NULL) != 0)
		{
			while ((int)--i >= 0)
				pthread_mutex_destroy(&all.info.forks[i]);
			return (1);
		}
		i++;
	}
	if (mutex_init(&all) != 0)
		return (1);
	philo_init(&all);
	return (0);
}
