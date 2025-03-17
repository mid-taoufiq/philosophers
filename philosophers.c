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



int main(int argc, char const **argv)
{
	int i = 1;
	if (argc != 5)
	{
		write(2, "Usage: \"philosophers number\" \"time to die\" \"time to eat\" \"sleep time\"\n", 70);
		exit(1);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			(write(2, "Error", 5), exit(1));
		i++;
	}
	
	return (0);
}