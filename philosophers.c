/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/31 18:06:59 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_init(t_info data)
{
	t_philo	*philos;
	int		i;
	int		j;

	i = 1;
	j = 0;
	philos = malloc(sizeof(t_philo) * (data.number_of_philos));
	while (i <= data.number_of_philos)
	{
		philos[j].id = i;
		i++;
		j++;
	}
	i = 0;
	while (i < 200)
	{
		printf("%d->", philos[i].id);
		i++;
	}
}

void	data_init(t_info *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	data->number_of_philos = check_number(argv[1]);
	data->time_to_die = check_number(argv[2]);
	data->time_to_eat = check_number(argv[3]);
	data->time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		data->number_of_times_philos_eat = check_number(argv[5]);
	philo_init(*data);
}

int	main(int argc, char **argv)
{
	t_info	data;

	data_init(&data, argc, argv);
	return (0);
}
