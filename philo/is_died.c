/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_died.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:09:37 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 22:19:22 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int is_time_to_die(DiningTable *table, int philosopher_index)
{
    long current_time = ft_time();
    return (current_time - table->philosophers[philosopher_index].last_meal > table->args->time_to_die);
}

int has_philosopher_eaten_enough(DiningTable *table, int philosopher_index) 
{
    return (table->args->number_of_times_each_philosopher_must_eat != -1 &&
           table->philosophers[philosopher_index].nbr_of_meals_eaten >= table->args->number_of_times_each_philosopher_must_eat);
}

int is_philosopher_dead(DiningTable *table) 
{
    int i;
    int check;

	i = 0;
	check = 0;
    while (i < table->args->num_philosophers)
    {
        if (is_time_to_die(table, i)) 
		{
            table->is_philosopher_dead = 1;
            table->philo_dead_id = table->philosophers[i].philosopher_id;
            printf("%ld %d died", (ft_time() - table->philosophers[i].start), table->philo_dead_id);
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
}
