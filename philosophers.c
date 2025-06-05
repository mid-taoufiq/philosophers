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

t_philo	*philo_init(t_info data, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;
	int		j;

	i = 1;
	j = 0;
	philos = malloc(sizeof(t_philo) * (data.philos_number));
	if (!philos)
		return (NULL); // (write(2, "something is wrong\n", 20), exit(1));
	while (j < data.philos_number)
	{
		philos[j].id = i;
		philos[j].left_fork = &forks[j];
		philos[j].right_fork = &forks[(j + 1) % data.philos_number];
		i++;
		j++;
	}
	i = 0;
	return (philos);
}

void	data_init(t_info *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	data->philos_number = check_number(argv[1]);
	data->time_to_die = check_number(argv[2]);
	data->time_to_eat = check_number(argv[3]);
	data->time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		data->number_of_times_philos_eat = check_number(argv[5]);
}

int	main(int argc, char **argv)
{
	t_info			data;
	int				i;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	i = 0;
	data_init(&data, argc, argv);
	forks = malloc(data.philos_number * sizeof(pthread_mutex_t));
	if (!forks)
		return (1);
	while (i < data.philos_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	philos = philo_init(data, forks);
	return (0);
}
