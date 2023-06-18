/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:00:57 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/18 22:26:01 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	status_print(t_Philosopher *philo, char *message)
{
	t_DiningTable	*table;
	table = (t_DiningTable *)philo->table;
	pthread_mutex_lock(table->mutex_print);
	printf("%ld %d %s\n", ft_time() - philo->start,
		philo->philosopher_id, message);
	pthread_mutex_unlock(table->mutex_print);
}

void	*routine(void *arg)
{
	t_Philosopher	*philo;
	t_DiningTable	*table;

	philo = (t_Philosopher *)arg;
	table = (t_DiningTable *)philo->table;
	if (philo->philosopher_id % 2 != 0)
		usleep(500);
	while (1)
	{
		status_print(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		status_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		status_print(philo, "has taken a fork");
		status_print(philo, "is eating");
		pthread_mutex_lock(table->mutex_meal);
		philo->last_meal = ft_time();
		pthread_mutex_unlock(table->mutex_meal);
		ft_sleep(table->args->time_to_eat);
		pthread_mutex_lock(table->mutex_meal);
		philo->nbr_of_meals_eaten += 1;
		pthread_mutex_unlock(table->mutex_meal);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		status_print(philo, "is sleeping");
		ft_sleep(table->args->time_to_sleep);
	}
	return (NULL);
}
// void	*routine(void *arg)
// {
// 	t_Philosopher	*philo;
// 	t_DiningTable	*table;

// 	philo = (t_Philosopher *)arg;
// 	table = (t_DiningTable *)philo->table;
// 	if (philo->philosopher_id % 2 != 0)
// 		usleep(500);
// 	while (1)
// 	{
// 		if (!table->is_philosopher_dead)
// 			printf("%ld %d is thinking\n", ft_time() - philo->start,
// 				philo->philosopher_id);
// 		pthread_mutex_lock(philo->left_fork);
// 		if (!table->is_philosopher_dead)
// 			printf("%ld %d has taken a fork\n", ft_time() - philo->start,
// 				philo->philosopher_id);
// 		pthread_mutex_lock(philo->right_fork);
// 		if (!table->is_philosopher_dead)
// 			printf("%ld %d has taken a fork\n", ft_time() - philo->start,
// 				philo->philosopher_id);
// 		if (!table->is_philosopher_dead)
// 			printf("%ld %d is eating\n", ft_time() - philo->start,
// 				philo->philosopher_id);
// 		philo->last_meal = ft_time();
// 		ft_sleep(table->args->time_to_eat, table);
// 		philo->nbr_of_meals_eaten += 1;
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		if (!table->is_philosopher_dead)
// 			printf("%ld %d is sleeping\n", ft_time() - philo->start,
// 				philo->philosopher_id);
// 		ft_sleep(table->args->time_to_sleep, table);
// 	}
// 	return (NULL);
// }
