/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_died.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:09:37 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/19 16:17:22 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_time_to_die(t_DiningTable *table, int p_index)
{
	long	current_time;
	long	diff;

	pthread_mutex_lock(table->mutex_meal);
	current_time = ft_time();
	diff = current_time - table->philosophers[p_index].last_meal;
	pthread_mutex_unlock(table->mutex_meal);
	return (diff > table->args->time_to_die);
}

int	has_philosopher_eaten_enough(t_DiningTable *t, int p_index)
{
	int	meals_eaten;

	meals_eaten = t->philosophers[p_index].nbr_of_meals_eaten;
	pthread_mutex_lock(t->mutex_meal);
	pthread_mutex_unlock(t->mutex_meal);
	return (t->args->ntpm_eat != -1
		&& meals_eaten >= t->args->ntpm_eat);
}

void	mark_philosopher_as_dead(t_DiningTable *table, int index)
{
	pthread_mutex_lock(table->mutex_death);
	table->is_philosopher_dead = 1;
	pthread_mutex_unlock(table->mutex_death);
	table->philo_dead_id = table->philosophers[index].philosopher_id;
}

void	print_philosopher_death(t_DiningTable *table, int index)
{
	pthread_mutex_lock(table->mutex_print);
	printf("%ld %d died\n", (ft_time() - table->philosophers[index].start),
		table->philo_dead_id);
	pthread_mutex_unlock(table->mutex_print);
}

int	is_philosopher_dead(t_DiningTable *table)
{
	int	i;
	int	check;
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(table->mutex_death);
	is_dead = table->is_philosopher_dead;
	pthread_mutex_unlock(table->mutex_death);
	if (is_dead)
		return (1);
	i = 0;
	check = 0;
	while (i < table->args->num_philosophers)
	{
		if (check_philosopher_death(table, i))
			return (1);
		if (has_philosopher_eaten_enough(table, i))
		{
			check += 1;
			if (check >= table->args->num_philosophers)
				return (1);
		}
		i++;
	}
	return (0);
}
