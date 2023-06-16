/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:04:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/12 00:05:42 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_and_store_arguments(int argc, char *argv[], DiningTable *table)
{
    table->args = malloc(sizeof(t_args));
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Error: Invalid number of arguments\n", 2);
        return 0;
    }
    table->args->num_philosophers = ft_atoi(argv[1]);
    if (table->args->num_philosophers <= 0)
    {
        ft_putstr_fd("Error: Invalid number of philosophers. Must be greater than 0\n", 2);
        return 0;
    }

    table->args->time_to_eat = ft_atoi(argv[3]);
    table->args->time_to_sleep = ft_atoi(argv[4]);
    table->args->time_to_die = ft_atoi(argv[2]);
    if (argc == 6)
    {
        table->args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
        if (table->args->number_of_times_each_philosopher_must_eat <= 0)
        {
            ft_putstr_fd("Error: Invalid number of times for each philosopher to eat. Must be greater than 0\n", 2);
            return 0;
        }
    }
    else
    {
        table->args->number_of_times_each_philosopher_must_eat = -1; // Default value when not specified
    }
    return (1);
}
