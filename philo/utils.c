/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:32:14 by tibarike          #+#    #+#             */
/*   Updated: 2025/07/08 10:35:05 by tibarike         ###   ########.fr       */
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
		if (result > INT_MAX)
			return (*success = -1, 0);
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
}

int	check_number(char *str)
{
	int	success;
	int	value;

	success = 0;
	value = ft_atoi(str, &success);
	if (success == -2)
	{
		write(2, "all numbers must be positive\n", 29);
		return (0);
	}
	else if (success == -1)
	{
		write(2, "enter a valid number\n", 22);
		return (0);
	}
	return (value);
}

void	ft_sleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = timer(0);
	while (timer(0) * 1000 - start * 1000 < time * 1000)
	{
		if (check_dead_fin(philo))
			break ;
		usleep(200);
	}
}

size_t	timer(int start)
{
	struct timeval	tv;
	size_t			current_time;
	static size_t	start_time;

	gettimeofday(&tv, NULL);
	current_time = (size_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (start)
		start_time = current_time;
	return (current_time - start_time);
}
