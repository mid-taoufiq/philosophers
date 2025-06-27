/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/27 17:49:34 by tibarike         ###   ########.fr       */
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

static bool	dead_part(t_philo *philo)
{
	size_t	current_time;
	size_t	flag;

	current_time = timer(0);
	sem_wait(philo->info->meal_time);
	flag = current_time - philo->last_meal;
	sem_post(philo->info->meal_time);
	if (flag > philo->info->time_to_die)
	{
		sem_wait(philo->info->meal_time);
		philo->info->dead_or_finished = 1;
		sem_post(philo->info->meal_time);
		sem_wait(philo->info->print);
		printf("%zu %d died\n", current_time, philo->id);
		return (true);
	}
	return (false);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (dead_part(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static void	routine(t_all *all, size_t i)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitoring, &all->philos[i]) == -1)
		return ;
	while (!check_dead_fin(all))
	{
		if (!check_dead_fin(all))
		{
			sem_wait(all->info.print);
			printf("%zu %ld is thinking\n", timer(0), i + 1);
			sem_post(all->info.print);
		}
		philo_take(i, all);
		philo_eat(i, all);
		philo_sleep(i, all);
	}
	pthread_join(monitor, NULL);
	exit(0);
}

bool	check_dead_fin(t_all *all)
{
	sem_wait(all->info.endflag);
	if (!all->info.dead_or_finished)
	{
		sem_post(all->info.endflag);
		return (false);
	}
	sem_post(all->info.endflag);
	return (true);
}

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
		else
			i++;
	}
	wait(&status);
	i = 0;
	while (i < all->info.philos_number)
		kill(pid[i++], SIGKILL);
	sem_close(all->info.forks);
	sem_close(all->info.print);
	sem_close(all->info.meal_time);
	sem_close(all->info.endflag);
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
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal_time");
	sem_unlink("/endflag");
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
