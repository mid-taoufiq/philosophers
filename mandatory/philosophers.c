/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/04 18:10:10 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_printer(char *action, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	if (!check_dead_fin(philo))
		printf("%zu %d %s\n", timer() - philo->info->start, id, action);
	pthread_mutex_unlock(&philo->info->print);
}

void	*monitoring(void *arg)
{
	t_all	*all;
	size_t	flag;
	size_t	i;

	all = (t_all *)arg;
	i = 0;
	flag = 0;
	while (1)
	{
		usleep(500);
		i = 0;
		while (i < all->info.philos_number)
		{
			pthread_mutex_lock(&all->info.meals_mutex);
			flag = (timer() - all->info.start) - all->philos[i].last_meal;
			pthread_mutex_unlock(&all->info.meals_mutex);
			if (flag > all->info.time_to_die)
			{
				pthread_mutex_lock(&all->info.endflag);
				all->info.dead_or_finished = 1;
				pthread_mutex_unlock(&all->info.endflag);
				pthread_mutex_lock(&all->info.print);
				printf("%zu %d died\n", timer() - all->info.start, all->philos[i].id);
				pthread_mutex_unlock(&all->info.print);
				return (0);
			}
			i++;
		}
	}
	
}

void	thinking_time(t_philo *philo)
{
	size_t	think_time;

	think_time = (philo->info->time_to_die - (timer() - philo->last_meal) - philo->info->time_to_eat) / 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time == 0)
		think_time = 1;
	if (think_time > 600)
		think_time = 200;
	action_printer("is thinking", philo->id, philo);
	ft_sleep(think_time, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	eat_time;

	eat_time = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		action_printer("is thinking", philo->id, philo);
	else
		thinking_time(philo);
	while (!check_dead_fin(philo))
	{
		pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
		action_printer("has taken a fork", philo->id, philo);
		pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
		action_printer("has taken a fork", philo->id, philo);
		eat_time = timer() - philo->info->start;
		pthread_mutex_lock(&philo->info->print);
		if (!check_dead_fin(philo))
			printf("%zu %d is eating\n", eat_time, philo->id);
		pthread_mutex_unlock(&philo->info->print);
		pthread_mutex_lock(&philo->info->meals_mutex);
		philo->last_meal = eat_time;
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->info->meals_mutex);
		ft_sleep(philo->info->time_to_eat, philo);
		pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
		action_printer("is sleeping", philo->id, philo);
		ft_sleep(philo->info->time_to_sleep, philo);
		thinking_time(philo);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		all;
	size_t		i;
	pthread_t	monitor;

	i = 0;
	if (argc != 5 && argc != 6)
		usage_error();
	all.info.philos_number = check_number(argv[1]);
	all.info.time_to_die = check_number(argv[2]);
	all.info.time_to_eat = check_number(argv[3]);
	all.info.time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		all.info.times_philo_must_eat = check_number(argv[5]);
	else
		all.info.times_philo_must_eat = 0;
	all.info.dead_or_finished = 0;
	all.info.start = timer();
	all.info.forks = malloc(sizeof(pthread_mutex_t) * all.info.philos_number);
	memset(all.info.forks, 0, sizeof(pthread_mutex_t) * all.info.philos_number);
	while (i < all.info.philos_number)
	{
		pthread_mutex_init(&all.info.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&all.info.meals_mutex, NULL);
	pthread_mutex_init(&all.info.print, NULL);
	pthread_mutex_init(&all.info.endflag, NULL);
	all.philos = malloc(sizeof(t_philo) * all.info.philos_number);
	memset(all.philos, 0, sizeof(t_philo) * all.info.philos_number);
	i = 0;
	while (i < all.info.philos_number)
	{
		all.philos[i].id = i + 1;
		all.philos[i].last_meal = timer() - all.info.start;
		all.philos[i].meals_eaten = 0;
		all.philos[i].finished = 0;
		if (all.philos[i].id % 2 != 0)
		{
			all.philos[i].left_fork = i;
			all.philos[i].right_fork = (i + 1) % all.info.philos_number;
		}
		else
		{
			all.philos[i].left_fork = (i + 1) % all.info.philos_number;
			all.philos[i].right_fork = i;
		}
		all.philos[i].info = &all.info;
		i++;
	}
	i = 0;
	while (i < all.info.philos_number)
	{
		pthread_create(&all.philos[i].thread, NULL, routine, &all.philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, &all);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < all.info.philos_number)
	{
		pthread_join(all.philos[i].thread, NULL);
		i++;
	}
	while (i < all.info.philos_number)
	{
		pthread_mutex_destroy(&all.info.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&all.info.meals_mutex);
	pthread_mutex_destroy(&all.info.print);
	pthread_mutex_destroy(&all.info.endflag);
	return (0);
}
