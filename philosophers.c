/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:38 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_routine(t_all *all)
{
	size_t		i;
	pthread_t	monitor;

	i = 0;
	while (i < all->info.philos_number)
	{
		pthread_create(&all->philos[i].thread, NULL, routine, &all->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, all);
	pthread_join(monitor, NULL);
}

void	join_threads(t_philo *philos, t_info info)
{
	size_t	i;

	i = 0;
	while (i < info.philos_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	philo_init(t_all *all)
{
	size_t		i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * (all->info.philos_number));
	if (!all->philos)
		return ;
	while (i < all->info.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].meals_eaten = 0;
		all->philos[i].left_fork = &all->info.forks[i];
		all->philos[i].right_fork = &all->info.forks[
			(i + 1) % all->info.philos_number];
		all->philos[i].info = &all->info;
		i++;
	}
	start_routine(all);
	join_threads(all->philos, all->info);
}

void	data_init(t_all *all, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	all->info.philos_number = check_number(argv[1]);
	all->info.time_to_die = check_number(argv[2]);
	all->info.time_to_eat = check_number(argv[3]);
	all->info.time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		all->info.number_of_times_philos_eat = check_number(argv[5]);
	else
		all->info.number_of_times_philos_eat = 0;
	all->info.dead_or_finished = 0;
	all->info.forks = malloc(all->info.philos_number * sizeof(pthread_mutex_t));
	if (!all->info.forks)
		return ;
}

int	main(int argc, char **argv)
{
	t_all		all;
	size_t		i;

	timer(1);
	i = 0;
	data_init(&all, argc, argv);
	while (i < all.info.philos_number)
	{
		pthread_mutex_init(&all.info.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&all.info.print, NULL);
	pthread_mutex_init(&all.info.endflag, NULL);
	pthread_mutex_init(&all.info.i, NULL);
	pthread_mutex_init(&all.info.meals_mutex, NULL);
	pthread_mutex_init(&all.info.time, NULL);
	philo_init(&all);
	return (0);
}
