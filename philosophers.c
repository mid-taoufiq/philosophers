/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/08 15:34:52 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_philo philo;

	if (argc != 5 && argc != 6)
		usage_error();
	philo.number_of_philos = check_positive(argv[1]);
	philo.time_to_die = check_positive(argv[2]);
	philo.time_to_eat = check_positive(argv[3]);
	philo.time_to_sleep = check_positive(argv[4]);
	if (argc == 6)
		philo.number_of_times_philos_eat = check_positive(argv[5]);
	return (0);
}