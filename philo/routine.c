/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:00:57 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/19 14:39:38 by aet-tass         ###   ########.fr       */
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

void	take_forks(t_Philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	status_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	status_print(philo, "has taken a fork");
}

void	eat(t_Philosopher *philo, t_DiningTable *table)
{
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
		take_forks(philo);
		eat(philo, table);
		status_print(philo, "is sleeping");
		ft_sleep(table->args->time_to_sleep);
	}
	return (NULL);
}
