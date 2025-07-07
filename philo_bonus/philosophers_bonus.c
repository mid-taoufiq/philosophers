/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/07 17:30:43 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	start_routine(t_info *info)
{
	size_t	i;
	int		status;

	timer(1);
	if (create_children(info) == -1)
		return ;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) == 1)
	{
		i = 0;
		while (i < info->philos_number)
		{
			kill(info->pid[i], SIGKILL);
			i++;
		}
	}
	i = 0;
	while (i < info->philos_number)
		waitpid(info->pid[i++], &status, 0);
	sem_post(info->print);
	close_sems(info);
	free(info->pid);
}

static void	sem_create(t_info *info)
{
	info->forks = sem_open("/forks", O_CREAT, 0666, info->philos_number);
	if (info->forks == SEM_FAILED)
		(sem_unlink("/forks"), exit(1));
	sem_unlink("/forks");
	info->print = sem_open("/print", O_CREAT, 0666, 1);
	if (info->print == SEM_FAILED)
		(sem_unlink("/print"), sem_close(info->forks), exit(1));
	sem_unlink("/print");
	info->meal_time = sem_open("/meal_time", O_CREAT, 0666, 1);
	if (info->meal_time == SEM_FAILED)
		(sem_unlink("/meal_time"), sem_close(info->print),
			sem_close(info->forks), exit(1));
	sem_unlink("/meal_time");
	info->wait_finished = sem_open("/wait_finished", O_CREAT, 0666, 1);
	if (info->wait_finished == SEM_FAILED)
		(sem_unlink("/wait_finished"), sem_close(info->print),
			sem_close(info->forks), sem_close(info->meal_time), exit(1));
	sem_unlink("/wait_finished");
	info->turn = sem_open("/turn", O_CREAT, 0666, 1);
	if (info->turn == SEM_FAILED)
		(sem_unlink("/turn"), sem_close(info->print),
			sem_close(info->wait_finished), sem_close(info->forks),
			sem_close(info->meal_time), exit(1));
	sem_unlink("/turn");
}

static void	data_init(t_info *info, int argc, char **argv)
{
	info->philos_number = check_number(argv[1]);
	info->time_to_die = check_number(argv[2]);
	info->time_to_eat = check_number(argv[3]);
	info->time_to_sleep = check_number(argv[4]);
	info->dead_or_finished = 0;
	if (argc == 6)
		info->times_philo_must_eat = check_number(argv[5]);
	else
		info->times_philo_must_eat = 0;
	sem_create(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		usage_error();
	data_init(&info, argc, argv);
	start_routine(&info);
	return (0);
}
