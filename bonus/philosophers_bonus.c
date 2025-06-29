/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/29 16:12:37 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	start_routine(t_all *all)
{
	size_t	i;
	pid_t	*pid;
	int		status;

	timer(1);
	i = 0;
	pid = malloc(sizeof(pid_t) * all->info.philos_number);
	if (!pid)
		return ;
	while (i < all->info.philos_number)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			routine(all, i);
		else if (pid[i] < 0)
		{
			sem_wait(all->info.print);
			ft_putstr_fd("fork failed", 2);
			sem_post(all->info.print);
			exit(0);
		}
		i++;
	}
	if (all->info.times_philo_must_eat > 0)
	{
		i = 0;
		while (i < all->info.philos_number)
		{
			sem_wait(all->info.wait);
			i++;
		}
	}
	else
		waitpid(-1, &status, 0);
	i = 0;
	while (i < all->info.philos_number)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	sem_post(all->info.print);
	sem_close(all->info.forks);
	sem_close(all->info.print);
	sem_close(all->info.meal_time);
	sem_close(all->info.endflag);
	sem_close(all->info.wait);
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
		all->philos[i].info = &all->info;
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
	all->info.forks = sem_open("/forks", O_CREAT,
			0644, all->info.philos_number);
	all->info.print = sem_open("/print", O_CREAT, 0644, 1);
	all->info.meal_time = sem_open("/meal_time", O_CREAT, 0644, 1);
	all->info.endflag = sem_open("/endflag", O_CREAT, 0644, 1);
	all->info.wait = sem_open("/wait", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal_time");
	sem_unlink("/endflag");
	sem_unlink("/wait");
	if (argc == 6)
		all->info.times_philo_must_eat = check_number(argv[5]);
	else
		all->info.times_philo_must_eat = 0;
	all->info.dead_or_finished = 0;
}

int	main(int argc, char **argv)
{
	t_all	all;

	data_init(&all, argc, argv);
	philo_init(&all);
	return (0);
}
