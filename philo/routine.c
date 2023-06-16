/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:00:57 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 23:06:36 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		if (!table->is_philosopher_dead)
			printf("%ld %d is thinking\n", ft_time() - philo->start,
				philo->philosopher_id);
		pthread_mutex_lock(philo->left_fork);
		if (!table->is_philosopher_dead)
			printf("%ld %d has taken a fork\n", ft_time() - philo->start,
				philo->philosopher_id);
		pthread_mutex_lock(philo->right_fork);
		if (!table->is_philosopher_dead)
			printf("%ld %d has taken a fork\n", ft_time() - philo->start,
				philo->philosopher_id);
		if (!table->is_philosopher_dead)
			printf("%ld %d is eating\n", ft_time() - philo->start,
				philo->philosopher_id);
		philo->last_meal = ft_time();
		ft_sleep(table->args->time_to_eat, table);
		philo->nbr_of_meals_eaten += 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!table->is_philosopher_dead)
			printf("%ld %d is sleeping\n", ft_time() - philo->start,
				philo->philosopher_id);
		ft_sleep(table->args->time_to_sleep, table);
	}
	return (NULL);
}
