/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/04 12:01:00 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitoring(t_all all)
{

}


void	routine(t_all all)
{
	while (!all.data.is_dead && !all.data.is_finished)
	{
		printf("philosopher %d is thinking\n", all.philos->id);
		if (all.philos->id % 2 == 0)
		{
			pthread_mutex_lock(&all.philos->left_fork);
			pthread_mutex_lock(&all.philos->right_fork);
			printf("philosopher %d is eating\n", all.philos->id);
			usleep(all.data.time_to_eat * 1000);
			printf("philosopher %d is sleeping\n", all.philos->id);
			usleep(all.data.time_to_sleep * 1000);
			all.philos->meals_eaten++;
			pthread_mutex_unlock(&all.philos->left_fork);
			pthread_mutex_unlock(&all.philos->right_fork);
		}
		else
		{
			pthread_mutex_lock(&all.philos->left_fork);
			pthread_mutex_lock(&all.philos->right_fork);
			printf("philosopher %d is eating\n", all.philos->id);
			usleep(all.data.time_to_eat * 1000);
			printf("philosopher %d is sleeping\n", all.philos->id);
			usleep(all.data.time_to_sleep * 1000);
			all.philos->meals_eaten++;
			pthread_mutex_unlock(&all.philos->left_fork);
			pthread_mutex_unlock(&all.philos->right_fork);
		}
	}
}


void	philo_init(t_all *all)
{
	int		j;
	int		i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * (all->data.philos_number));
	if (!all->philos)
		return ;
	while (i < all->data.philos_number)
	{
		all->philos[i].id = i + 1;
		all->philos[i].meals_eaten = 0;
		all->philos[i].left_fork = &all->data.forks[i];
		all->philos[i].right_fork = &all->data.forks[
			(i + 1) % all->data.philos_number];
		pthread_create(&all->philos[i].thread, NULL, routine, &all);
		i++;
	}
}

void	data_init(t_all *all, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	all->data.philos_number = check_number(argv[1]);
	all->data.time_to_die = check_number(argv[2]);
	all->data.time_to_eat = check_number(argv[3]);
	all->data.time_to_sleep = check_number(argv[4]);
	all->data.forks = malloc(all->data.philos_number * sizeof(pthread_mutex_t));
	if (!all->data.forks)
		return ;
	all->data.is_dead = 0;
	all->data.is_finished = 0;
	if (argc == 6)
		all->data.number_of_times_philos_eat = check_number(argv[5]);
}

int	main(int argc, char **argv)
{
	t_all		all;
	pthread_t	monitor;
	int			i;

	i = 0;
	pthread_create(&monitor, NULL, monitoring, &all);
	data_init(&all, argc, argv);
	while (i < all.data.philos_number)
	{
		pthread_mutex_init(&all.data.forks[i], NULL);
		i++;
	}
	philo_init(&all);
	return (0);
}
