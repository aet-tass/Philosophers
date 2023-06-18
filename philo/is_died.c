/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_died.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:09:37 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/18 22:59:12 by aet-tass         ###   ########.fr       */
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

/*int	is_philosopher_dead(t_DiningTable *table)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < table->args->num_philosophers)
	{
		if (is_time_to_die(table, i))
		{
			pthread_mutex_lock(table->mutex_print);
			pthread_mutex_lock(table->mutex_death);
			table->is_philosopher_dead = 1;
			pthread_mutex_unlock(table->mutex_death);
			table->philo_dead_id = table->philosophers[i].philosopher_id;
			printf("%ld %d died", (ft_time() - table->philosophers[i].start),
				table->philo_dead_id);
			return (1);
		}
		if (has_philosopher_eaten_enough(table, i))
		{
			check += (1);
			if (check >= table->args->num_philosophers)
				return (1);
		}
		i++;
	}
	return (0);
}*/
void mark_philosopher_as_dead(t_DiningTable *table, int index)
{
    pthread_mutex_lock(table->mutex_death);
    table->is_philosopher_dead = 1;
    pthread_mutex_unlock(table->mutex_death);

    table->philo_dead_id = table->philosophers[index].philosopher_id;
}

void print_philosopher_death(t_DiningTable *table, int index)
{
    pthread_mutex_lock(table->mutex_print);
    printf("%ld %d died\n", (ft_time() - table->philosophers[index].start),
           table->philo_dead_id);
    pthread_mutex_unlock(table->mutex_print);
}

int is_philosopher_dead(t_DiningTable *table)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while (i < table->args->num_philosophers)
    {
        if (is_time_to_die(table, i))
        {
            mark_philosopher_as_dead(table, i);
            print_philosopher_death(table, i);
            return 1;
        }
        if (has_philosopher_eaten_enough(table, i))
        {
            check += 1;
            if (check >= table->args->num_philosophers)
                return 1;
        }
        i++;
    }
    return 0;
}

