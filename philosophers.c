/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:35:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/06/02 18:03:39 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ss;
	size_t	i;

	ss = (char *) s;
	i = 0;
	while (i < n)
	{
		ss[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*tmp;
	size_t	total;

	total = num * size;
	if (num != 0 && (size != total / num))
		return (NULL);
	if (num == 0 || size == 0)
	{
		tmp = malloc(0);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = malloc(num * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, num * size);
	return (tmp);
}

void	philo_init(t_info data, int *forks)
{
	t_philo	*philos;
	int		i;
	int		j;

	i = 1;
	j = 0;
	philos = malloc(sizeof(t_philo) * (data.philos_number));
	if (!philos)
		return ;
	while (j < data.philos_number)
	{
		philos[j].id = i;
		philos->left_fork = forks[j];
		philos->right_fork = forks[(j + 1) % data.philos_number];
		i++;
		j++;
	}
	i = 0;
}

void	data_init(t_info *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		usage_error();
	data->philos_number = check_number(argv[1]);
	data->time_to_die = check_number(argv[2]);
	data->time_to_eat = check_number(argv[3]);
	data->time_to_sleep = check_number(argv[4]);
	if (argc == 6)
		data->number_of_times_philos_eat = check_number(argv[5]);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		*forks;

	data_init(&data, argc, argv);
	forks = ft_calloc(data.philos_number, sizeof(int));
	philo_init(data, forks);
	return (0);
}
