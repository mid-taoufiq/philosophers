/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/18 15:01:41 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static bool	check_finished(t_all *all)
{
	size_t	j;

	j = 0;
	while (j < all->info.philos_number)
	{
		if (all->philos[j].finished == 1)
			j++;
		else
			break ;
	}
	if (j == all->info.philos_number)
		return (true);
	else
		return (false);
}

static bool	finished_part(t_all *all, size_t i)
{
	if (check_finished(all))
	{
		all->info.dead_or_finished = 1;
		return (true);
	}
	if (all->philos[i].meals_eaten == all->info.times_philo_must_eat)
		all->philos[i].finished = 1;
	return (false);
}

static bool	dead_part(t_all *all, size_t i)
{
	size_t	current_time;
	size_t	flag;

	current_time = timer(0);
	flag = current_time - all->philos[i].last_meal;
	if (flag > all->info.time_to_die)
	{
		all->info.dead_or_finished = 1;
		printf("%zu %lu died\n", current_time, i + 1);
		return (true);
	}
	return (false);
}

void	monitoring(t_all *all)
{
	size_t	i;

	while (1)
	{
		usleep(10);
		i = 0;
		while (i < all->info.philos_number)
		{
			if (dead_part(all, i))
				return ;
			if (all->info.times_philo_must_eat > 0)
			{
				if (finished_part(all, i))
					return ;
			}
			i++;
		}
	}
	return ;
}

static void	routine(t_all *all, size_t philon, sem_t **forks, sem_t **print)
{
	while (!all->info.dead_or_finished)
	{
		philo_take(philon, forks, print);
		philo_eat(philon, all, forks, print);
		philo_sleep(philon, all, print);
	}
	exit(0);
}

static void	start_routine(t_all *all, sem_t **forks, sem_t **print)
{
	size_t	i;
	pid_t	pid;
	size_t	time;

	i = 0;
	while (i < all->info.philos_number)
	{
		pid = fork();
		if (!pid)
		{
			time = timer(0);
			sem_wait(*print);
			printf("%zu %ld is sleeping\n", time, i + 1);
			sem_post(*print);
			routine(all, i + 1, forks, print);
		}
		else
			i++;
	}
}

static void	philo_init(t_all *all)
{
	size_t	i;
	sem_t	*forks;
	sem_t	*print;

	all->philos = malloc(sizeof(t_philo) * (all->info.philos_number));
	if (!all->philos)
		return ;
	forks = sem_open("/forks", O_CREAT, 0777, all->info.philos_number);
	print = sem_open("/print", O_CREAT, 0777, 1);
	i = 0;
	while (i < all->info.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].finished = 0;
		all->philos[i].meals_eaten = 0;
		all->philos[i].last_meal = 0;
		all->philos[i].info = &all->info;
		i++;
	}
	start_routine(all, &forks, &print);
}

static void	data_init(t_all *all, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
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

int	main(int argc, char **argv)
{
	t_all	all;

	timer(1);
	data_init(&all, argc, argv);
	philo_init(&all);
	return (0);
}
