/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:32:14 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/11 16:02:55 by tibarike         ###   ########.fr       */
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

int	check_number(char *str)
{
	int	success;
	int	value;

	success = 0;
	value = ft_atoi(str, &success);
	if (success == -2)
	{
		write(2, "all numbers must positive\n", 27);
		exit(1);
	}
	else if (success == -1)
	{
		write(2, "entre a valid numbers\n", 23);
		exit(1);
	}
	return (value);
}

int	ft_atoi(char *nb, int *success)
{
	int		i;
	long	result;
	int		signal;

	i = 0;
	result = 0;
	signal = 1;
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
		result = (result * 10);
		result += (nb[i++] - '0');
	}
	if (nb[i])
		return (*success = -1, 0);
	return (result * signal);
}

void	ft_sleep(size_t time, t_philo *philo)
{
	size_t	i;

	i = 0;
	time = time * 1000;
	while (!philo->info->dead_or_finished && i < time)
	{
		usleep(300);
		i += 300;
	}
}

size_t	timer(int start)
{
	struct timeval	tv;
	size_t			current_time;
	static size_t	start_time;

	gettimeofday(&tv, NULL);
	current_time = (size_t)tv.tv_usec / 1000 + tv.tv_sec * 1000;
	if (start)
		start_time = current_time;
	return (current_time - start_time);
}
