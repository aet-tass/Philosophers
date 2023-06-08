/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:04:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/08 18:04:11 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void store_arguments(int argc, char *argv[], DiningTable *table) {
    if (argc < 5 || argc > 6) {
        ft_putstr_fd("Error: Invalid number of arguments\n", 2);
        exit(1);
    }

    table->num_philosophers = ft_atoi(argv[1]);

    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * table->num_philosophers);
    if (table->philosophers == NULL) {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        exit(1);
    }

    int i;
    for (i = 0; i < table->num_philosophers; i++) {
        Philosopher *philosopher = &(table->philosophers[i]);
        philosopher->philosopher_id = i + 1;
        philosopher->time_to_die = ft_atoi(argv[2]);
        philosopher->time_to_eat = ft_atoi(argv[3]);
        philosopher->time_to_sleep = ft_atoi(argv[4]);
        if (argc == 6) {
            philosopher->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
        } else {
            philosopher->number_of_times_each_philosopher_must_eat = -1; // Default value when not specified
        }
        // Initialize the mutexes for the forks
        philosopher->left_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
        philosopher->right_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
        if (philosopher->left_fork == NULL || philosopher->right_fork == NULL) {
            ft_putstr_fd("Error: Memory allocation failed\n", 2);
            exit(1);
        }
        pthread_mutex_init(philosopher->left_fork, NULL);
        pthread_mutex_init(philosopher->right_fork, NULL);
    }
}
