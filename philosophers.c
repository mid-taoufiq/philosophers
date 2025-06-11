/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/11 15:36:45 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_routine(t_philo *philos, t_info info)
{
	int	i;

	i = 0;
	while (i < info.philos_number)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}

void	join_philos(t_philo *philos, t_info info)
{
	int	i;

	i = 0;
	while (i < info.philos_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	philo_init(t_info info)
{
	t_philo		*philos;
	// pthread_t	monitor;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philo) * (info.philos_number));
	if (!philos)
		return ;
	while (i < info.philos_number)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &info.forks[i];
		philos[i].right_fork = &info.forks[
			(i + 1) % info.philos_number];
		philos[i].info = &info;
		i++;
	}
	// pthread_create(&monitor, NULL, monitor, &philos);
	start_routine(philos, info);
	join_philos(philos, info);
	// pthread_join(monitor, NULL);
}

void	data_init(t_info *info, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	info->philos_number = check_number(argv[1]);
	info->time_to_die = check_number(argv[2]);
	info->time_to_eat = check_number(argv[3]);
	info->time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		info->number_of_times_philos_eat = check_number(argv[5]);
	info->dead_or_finished = 0;
	info->forks = malloc(info->philos_number * sizeof(pthread_mutex_t));
	if (!info->forks)
		return ;
}

int	main(int argc, char **argv)
{
	t_info		info;
	int			i;

	timer(1);
	i = 0;
	data_init(&info, argc, argv);
	while (i < info.philos_number)
	{
		pthread_mutex_init(&info.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&info.print, NULL);
	pthread_mutex_init(&info.endflag, NULL);
	pthread_mutex_init(&info.time, NULL);
	philo_init(info);
	return (0);
}
