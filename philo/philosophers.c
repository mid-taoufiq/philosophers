/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/07 17:26:03 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	start_routine(t_all *all)
{
	size_t		i;
	pthread_t	monitor;

	timer(1);
	i = 0;
	while (i < all->info.philos_number)
	{
		if (pthread_create(&all->philos[i].thread, NULL,
				routine, &all->philos[i]) != 0)
		{
			while ((int)--i >= 0)
				pthread_join(all->philos[i].thread, NULL);
			return (false);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, all) != 0)
	{
		i = 0;
		while (i < all->info.philos_number)
			pthread_join(all->philos[i++].thread, NULL);
		return (false);
	}
	pthread_join(monitor, NULL);
	return (true);
}

static bool	mutex_init(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < all->info.philos_number)
	{
		if (pthread_mutex_init(&all->info.forks[i], NULL) != 0)
		{
			while ((int)--i >= 0)
				pthread_mutex_destroy(&all->info.forks[i]);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&all->info.meals_mutex, NULL) != 0)
		return (destroy_forks(all), false);
	if (pthread_mutex_init(&all->info.print, NULL) != 0)
		return (destroy_forks(all),
			pthread_mutex_destroy(&all->info.meals_mutex), false);
	if (pthread_mutex_init(&all->info.endflag, NULL) != 0)
		(destroy_forks(all), pthread_mutex_destroy(&all->info.print),
			pthread_mutex_destroy(&all->info.meals_mutex), false);
	return (true);
}

static void	info_init(t_all *all, int argc, char **argv)
{
	all->info.philos_number = check_number(argv[1]);
	all->info.time_to_die = check_number(argv[2]);
	all->info.time_to_eat = check_number(argv[3]);
	all->info.time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		all->info.times_philo_must_eat = check_number(argv[5]);
	else
		all->info.times_philo_must_eat = 0;
	all->info.dead_or_finished = 0;
}

static bool	philo_init(t_all *all)
{
	size_t	i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * all->info.philos_number);
	if (!all->philos)
		return (false);
	memset(all->philos, 0, sizeof(t_philo) * all->info.philos_number);
	while (i < all->info.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].last_meal = 0;
		all->philos[i].meals_eaten = 0;
		all->philos[i].finished = 0;
		all->philos[i].left_fork = i;
		all->philos[i].right_fork = (i + 1) % all->info.philos_number;
		all->philos[i].info = &all->info;
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_all		all;
	size_t		i;

	i = 0;
	info_init(&all, argc, argv);
	all.info.forks = malloc(sizeof(pthread_mutex_t) * all.info.philos_number);
	if (!all.info.forks)
		return (1);
	memset(all.info.forks, 0, sizeof(pthread_mutex_t) * all.info.philos_number);
	if (!mutex_init(&all))
		return (free(all.info.forks), 1);
	if (!philo_init(&all))
		return (free(all.info.forks), 1);
	if (!start_routine(&all))
		return (free(all.info.forks), free(all.philos), 1);
	i = 0;
	while (i < all.info.philos_number)
	{
		pthread_join(all.philos[i].thread, NULL);
		i++;
	}
	destroy_remainings(&all);
	free(all.info.forks);
	free(all.philos);
	return (0);
}
