/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:21:24 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 22:22:47 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void initialize_mutexes(DiningTable *table) 
{
    table->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->args->num_philosophers);
    int i = 0;
    while (i < table->args->num_philosophers) 
	{
        pthread_mutex_init(&(table->mutex[i]), NULL);
        i++;
    }
}
   
void initialize_philosophers(DiningTable *table) 
{
    long time = ft_time();
    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * table->args->num_philosophers);
    int i = 0;
    while (i < table->args->num_philosophers) {
        table->philosophers[i].last_meal = time;
        table->philosophers[i].nbr_of_meals_eaten = 0;
        table->philosophers[i].table = table;
        table->philosophers[i].args = table->args;
        table->philosophers[i].start = time;
        table->philosophers[i].philosopher_id = i + 1;
        table->philosophers[i].left_fork = &table->mutex[i];
        table->philosophers[i].right_fork = &table->mutex[(i + 1) % table->args->num_philosophers];
        i++;
    }
}

void initialize_threads(DiningTable *table) 
{
    table->threads = (pthread_t *)malloc(sizeof(pthread_t) * table->args->num_philosophers);
    int i = 0;
    while (i < table->args->num_philosophers) {
        pthread_create(&table->threads[i], NULL, routine, &table->philosophers[i]);
        i++;
    }
}

void initialize_table(DiningTable *table) 
{
    initialize_mutexes(table);
    initialize_philosophers(table);
    initialize_threads(table);
}

