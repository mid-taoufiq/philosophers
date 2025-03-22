/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:32:27 by tibarike          #+#    #+#             */
/*   Updated: 2025/03/17 00:34:33 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	number_of_philos;
	int	time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	number_of_times_philos_eat;
}	t_philo;



int	ft_atoi(char *nb);



#endif