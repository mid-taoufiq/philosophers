/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/02 15:51:53 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	start_routine(t_all *all)
{
	size_t	i;
	int		status;

	timer(1);
	if (create_children(all) == -1)
		return ;
	if (all->info.times_philo_must_eat > 0)
	{
		i = 0;
		while (i < all->info.philos_number)
		{
			sem_wait(all->info.wait_finished);
			i++;
		}
	}
	else
		waitpid(-1, &status, 0);
	i = 0;
	while (i < all->info.philos_number)
	{
		kill(all->info.pid[i], SIGKILL);
		i++;
	}
	(sem_post(all->info.print), close_sems(&all->info));
	free(all->info.pid);
}

static void	data_init(t_all *all, int argc, char **argv)
{
	all->info.philos_number = check_number(argv[1]);
	all->info.time_to_die = check_number(argv[2]);
	all->info.time_to_eat = check_number(argv[3]);
	all->info.time_to_sleep = check_number(argv[4]);
	all->info.dead_or_finished = 0;
	if (argc == 6)
		all->info.times_philo_must_eat = check_number(argv[5]);
	else
		all->info.times_philo_must_eat = 0;
	sems_create(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 5 && argc != 6)
		usage_error();
	data_init(&all, argc, argv);
	start_routine(&all);
	return (0);
}
