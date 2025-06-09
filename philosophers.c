/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/09 13:10:36 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	monitoring(t_all all)
// {

// }


void	*routine(void *arg)
{
	t_philo *philos;

	philos = arg;
	printf ("fsdfjhkjfd\n");
	// while (!all.data.is_dead && !all.data.is_finished)
	// {
	// 	printf("philosopher %d is thinking\n", all.philos->id);
	// 	if (all.philos->id % 2 == 0)
	// 	{
	// 		pthread_mutex_lock(&all.philos->left_fork);
	// 		pthread_mutex_lock(&all.philos->right_fork);
	// 		printf("philosopher %d is eating\n", all.philos->id);
	// 		usleep(all.data.time_to_eat * 1000);
	// 		printf("philosopher %d is sleeping\n", all.philos->id);
	// 		usleep(all.data.time_to_sleep * 1000);
	// 		all.philos->meals_eaten++;
	// 		pthread_mutex_unlock(&all.philos->left_fork);
	// 		pthread_mutex_unlock(&all.philos->right_fork);
	// 	}
	// 	else
	// 	{
	// 		pthread_mutex_lock(&all.philos->left_fork);
	// 		pthread_mutex_lock(&all.philos->right_fork);
	// 		printf("philosopher %d is eating\n", all.philos->id);
	// 		usleep(all.data.time_to_eat * 1000);
	// 		printf("philosopher %d is sleeping\n", all.philos->id);
	// 		usleep(all.data.time_to_sleep * 1000);
	// 		all.philos->meals_eaten++;
	// 		pthread_mutex_unlock(&all.philos->left_fork);
	// 		pthread_mutex_unlock(&all.philos->right_fork);
	// 	}
	// }
	return (NULL);
}

void	start_routine(t_philo)

void	join_philos(t_info info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info.philos_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	philo_init(t_info info, t_data data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * (info.philos_number));
	if (!philos)
		return (NULL);
	while (i < info.philos_number)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &data.forks[i];
		philos[i].right_fork = &data.forks[
			(i + 1) % info.philos_number];
	}
}

void	data_init(t_info *info, t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	info->philos_number = check_number(argv[1]);
	info->time_to_die = check_number(argv[2]);
	info->time_to_eat = check_number(argv[3]);
	info->time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		info->number_of_times_philos_eat = check_number(argv[5]);
	data->is_finished = 0;
	data->is_dead = 0;
	data->forks = malloc(info->philos_number * sizeof(pthread_mutex_t));
	if (!data->forks)
		return ;
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;
	int			i;

	i = 0;
	// pthread_create(&monitor, NULL, monitoring, &all);
	data_init(&info, &data, argc, argv);
	while (i < info.philos_number)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	philo_init(info, data);
	return (0);
}
