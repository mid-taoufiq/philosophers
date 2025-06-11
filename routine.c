#include "philosophers.h"

void	even_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->print);
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	usleep(philo->info->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	usleep(philo->info->time_to_sleep * 1000);
}

void	odd_eat_sleep(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->print);
	printf(" %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	usleep(philo->info->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->info->print);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->info->print);
	usleep(philo->info->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->info->is_dead && !philo->info->is_finished)
	{
		if (philo->id % 2 == 0)
			even_eat_sleep(philo);
		pthread_mutex_lock(&philo->info->print);
		printf("%d is thinking\n", philo->id);
		pthread_mutex_unlock(&philo->info->print);
		if (philo->id % 2 != 0)
			odd_eat_sleep(philo);
	}
	return (0);
}
