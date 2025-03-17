/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:32:14 by tibarike          #+#    #+#             */
/*   Updated: 2025/03/17 00:34:26 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
