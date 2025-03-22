/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/03/17 00:37:22 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usage_error(void)
{
	write(2, "Usage:  \"philosophers number\"", 30);
	write(2, " \"time to die\"", 15);
	write(2, " \"time to eat\"", 15);
	write(2, " \"time to sleep\"", 17);
	write(2, " (op) \"number of time each philo must eat\"\n", 44);
	exit(1);
}

int	check_positive(char *str)
{
	int value;

	value = ft_atoi(str);
	if (value <= 0)
	{
		write(2, "all numbers must positive", 26),
		exit(1);
	}
	return (value);
}

int main(int argc, char **argv)
{
	int i = 2;
	t_philo philo;

	if (argc != 5 && argc != 6)
		usage_error();
	philo.number_of_philos = ft_atoi(argv[1]);
	if (philo.number_of_philos <= 0)
		(write (2, "number of philos must be 1 or plus", 35), exit(1));
	philo.time_to_die = check_positive(argv[2]);
	philo.time_to_eat = check_positive(argv[3]);
	philo.time_to_sleep = check_positive(argv[4]);
	if (argc == 6)
		philo.number_of_times_philos_eat = check_positive(argv[5]);
	return (0);
}