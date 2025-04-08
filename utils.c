/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:32:14 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/08 15:33:45 by tibarike         ###   ########.fr       */
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

int	ft_atoi(char *nb)
{
	int		i;
	long	result;
	int		signal;
	long	check;

	i = 0;
	result = 0;
	signal = 1;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			signal = -1;
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		check = result;
		result = (result * 10);
		result += (nb[i++] - '0');
	}
	return (result * signal);
}
