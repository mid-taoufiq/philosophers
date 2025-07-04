/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:32:14 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/04 15:50:59 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nb, int *success)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			return (*success = -2, 0);
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		result = (result * 10) + (nb[i] - '0');
		i++;
	}
	if (nb[i] || result == 0)
		return (*success = -1, 0);
	return ((int)result);
}

void	usage_error(void)
{
	write(2, "Usage:  \"philosophers number\"", 30);
	write(2, " \"time to die\"", 15);
	write(2, " \"time to eat\"", 15);
	write(2, " \"time to sleep\"", 17);
	write(2, " (op) \"number of time each philo must eat\"\n", 44);
	exit(1);
}

int	check_number(char *str)
{
	int	success;
	int	value;

	success = 0;
	value = ft_atoi(str, &success);
	if (success == -2)
	{
		write(2, "all numbers must positive\n", 27);
		return (0);
	}
	else if (success == -1)
	{
		write(2, "entre a valid numbers\n", 23);
		return (0);
	}
	return (value);
}

void	ft_sleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = timer();
	while (timer() - start < time)
	{
		pthread_mutex_lock(&philo->info->endflag);
		if (philo->info->dead_or_finished)
		{
			pthread_mutex_unlock(&philo->info->endflag);
			break ;
		}
		pthread_mutex_unlock(&philo->info->endflag);
		usleep(100);
	}
}

size_t	timer(void)
{
	struct timeval	tv;
	size_t			current_time;

	gettimeofday(&tv, NULL);
	current_time = (size_t)tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return (current_time);
}
