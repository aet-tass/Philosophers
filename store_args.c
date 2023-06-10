/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:04:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/10 23:21:24 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_and_store_arguments(int argc, char *argv[], DiningTable *table)
{
    t_args args;

    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Error: Invalid number of arguments\n", 2);
        return 0;
    }

    args.num_philosophers = ft_atoi(argv[1]);

    if (args.num_philosophers <= 0)
    {
        ft_putstr_fd("Error: Invalid number of philosophers. Must be greater than 0\n", 2);
        return 0;
    }

    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * args.num_philosophers);
    if (table->philosophers == NULL)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return 0;
    }

    int i;
    for (i = 0; i < args.num_philosophers; i++)
    {
        //Philosopher *philosopher = &(table->philosophers[i]);
        args.time_to_die = ft_atoi(argv[2]);
        args.time_to_eat = ft_atoi(argv[3]);
        args.time_to_sleep = ft_atoi(argv[4]);

        if (argc == 6)
        {
            args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
            if (args.number_of_times_each_philosopher_must_eat <= 0)
            {
                ft_putstr_fd("Error: Invalid number of times for each philosopher to eat. Must be greater than 0\n", 2);
                return 0;
            }
        }
        else
        {
            args.number_of_times_each_philosopher_must_eat = -1; // Default value when not specified
        }
        table->args = &args;
    }

    return 1;
}

// int main(int argc, char *argv[])
// {
//     DiningTable table;

//     if (!check_and_store_arguments(argc, argv, &table))
//     {
//         // Arguments checking failed, exit the program
//         return 1;
//     }

//     // Continue with the program logic using the stored arguments in the 'table' variable

//     return 0;
// }

