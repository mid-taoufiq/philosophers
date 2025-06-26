/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/26 15:54:34 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
 
// static bool	check_finished(t_all *all)
// {
// 	size_t	j;

// 	j = 0;
// 	while (j < all->info.philos_number)
// 	{
// 		if (all->philos[j].finished == 1)
// 			j++; 
// 		else
// 			break ;
// 	}
// 	if (j == all->info.philos_number)
// 		return (true);
// 	else
// 		return (false);
// }

// static bool	finished_part(t_all *all, size_t i)
// {
// 	if (check_finished(all))
// 	{
// 		all->info.dead_or_finished = 1;
// 		return (true);
// 	}
// 	if (all->philos[i].meals_eaten == all->info.times_philo_must_eat)
// 		all->philos[i].finished = 1;
// 	return (false);
// }

static bool	dead_part(t_all *all, size_t i)
{
	size_t	current_time;
	size_t	flag;

	current_time = timer(0);
	sem_wait(all->info.meal_time);
	flag = timer(0) - all->philos[i].last_meal;
	sem_post(all->info.meal_time);
	if (flag > all->info.time_to_die)
	{
		all->info.dead_or_finished = 1;
		sem_wait(all->info.print);
		printf("%zu %lu died\n", current_time, i + 1);
		sem_post(all->info.print);
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
			i++;
		}
	}
	return ;
}


static void	routine(t_all *all, size_t philon)
{
	while (!all->info.dead_or_finished)
	{
		philo_take(philon, all);
		philo_eat(philon, all);
		philo_sleep(philon, all);
		dead_part(all, philon);
	}
}

static void	start_routine(t_all *all)
{
	size_t	i;
	pid_t	*pid;
	size_t	time;

	i = 0;
	pid = malloc(sizeof(pid_t) * all->info.philos_number);
	if (!pid)
		return ;
	while (i < all->info.philos_number)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			time = timer(0);
			sem_wait(all->info.print);
			if (!all->info.dead_or_finished)
				printf("%zu %ld is thinking\n", time, i + 1);
			sem_post(all->info.print);
			routine(all, i);
			exit(0);
		}
		else
			i++;
	}
	monitoring(all);
	for (i = 0; i < all->info.philos_number; i++)
		kill(pid[i], SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_close(all->info.forks);
	sem_close(all->info.print);
}

static void	philo_init(t_all *all)
{
	size_t	i;

	all->philos = malloc(sizeof(t_philo) * (all->info.philos_number));
	if (!all->philos)
		return ;
	i = 0;
	while (i < all->info.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].finished = 0;
		all->philos[i].meals_eaten = 0;
		all->philos[i].last_meal = 0;
		i++;
	}
	start_routine(all);
}

static void	data_init(t_all *all, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	all->info.philos_number = check_number(argv[1]);
	all->info.time_to_die = check_number(argv[2]);
	all->info.time_to_eat = check_number(argv[3]);
	all->info.time_to_sleep = check_number(argv[4]);
	all->info.forks = sem_open("/forks", O_CREAT, 0644, all->info.philos_number);
	all->info.print = sem_open("/print", O_CREAT, 0644, 1);
	all->info.meal_time = sem_open("/meal_time", O_CREAT, 0644, 1);
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
