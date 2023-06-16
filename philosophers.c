/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 18:07:21 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    ft_sleep(int time, DiningTable *table)
{
    long start;

    start = ft_time();
    while(ft_time() - start < time && !table->is_philosopher_dead)
        usleep(500);
}
long ft_time(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return time_in_ms;
}

void ft_detach(DiningTable *table)
{
    for (int i = 0; i < table->args->num_philosophers; i++)
    {
        pthread_detach(table->threads[i]);
    }
    for (int i = 0; i < table->args->num_philosophers; i++)
    {
        pthread_mutex_destroy(&table->mutex[i]);
    }
}

int is_philosopher_dead(DiningTable *table) {
    int i;
    int check = 0;
    long current_time = ft_time();

    for (i = 0; i < table->args->num_philosophers; i++)
    {
        if (current_time - table->philosophers[i].last_meal > table->args->time_to_die) {
            table->is_philosopher_dead = 1;
            table->philo_dead_id = table->philosophers[i].philosopher_id;
            printf("%ld %d died", (ft_time() - table->philosophers[i].start), table->philo_dead_id);
            return 1;
        }
        if (table->args->number_of_times_each_philosopher_must_eat != -1)
        {
            if (table->philosophers[i].nbr_of_meals_eaten  >= table->args->number_of_times_each_philosopher_must_eat)
            {
                check += 1;
                if (check >= table->args->num_philosophers)
                    return (1);
            }
        }
    }
    return 0;
}

void *routine(void *arg)
{
    Philosopher *philo = (Philosopher *)arg;
    DiningTable *table = (DiningTable *)philo->table;
    if (philo->philosopher_id % 2 != 0)
        usleep(500);
    while (1)
    {
        if (!table->is_philosopher_dead)
            printf("%ld %d is thinking\n",ft_time() - philo->start, philo->philosopher_id);
        pthread_mutex_lock(philo->left_fork);
        if (!table->is_philosopher_dead)
            printf("%ld %d has taken a fork\n", ft_time() - philo->start, philo->philosopher_id);
        pthread_mutex_lock(philo->right_fork);
        if (!table->is_philosopher_dead)
            printf("%ld %d has taken a fork\n", ft_time() - philo->start,  philo->philosopher_id);
        if (!table->is_philosopher_dead)
            printf("%ld %d is eating\n",ft_time() - philo->start,  philo->philosopher_id);
        philo->last_meal = ft_time();
        ft_sleep(table->args->time_to_eat, table);
        philo->nbr_of_meals_eaten += 1;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        if (!table->is_philosopher_dead)
            printf("%ld %d is sleeping\n",ft_time() - philo->start,  philo->philosopher_id);
        ft_sleep(table->args->time_to_sleep, table);
    }
    return NULL;
}

void initialize_table(DiningTable *table)
{
    table->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->args->num_philosophers);
    for (int i = 0; i < table->args->num_philosophers; i++)
    {
        pthread_mutex_init(&(table->mutex[i]), NULL);
    }

    int i;

    long time = ft_time();
    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * table->args->num_philosophers);
    for (i = 0; i < table->args->num_philosophers; i++)
    {
        table->philosophers[i].last_meal = time;
        table->philosophers[i].nbr_of_meals_eaten = 0;
        table->philosophers[i].table = table;
        table->philosophers[i].args = table->args;
        table->philosophers[i].start = time;
        table->philosophers[i].philosopher_id = i + 1;
        table->philosophers[i].left_fork = &table->mutex[i];
        table->philosophers[i].right_fork = &table->mutex[(i + 1) % table->args->num_philosophers];

    }
    table->threads = (pthread_t *)malloc(sizeof(pthread_t) * table->args->num_philosophers);
    for (i = 0; i < table->args->num_philosophers; i++)
    {
        pthread_create(&table->threads[i], NULL, routine, &table->philosophers[i]);
    }
}

int main(int argc, char *argv[])
{
    DiningTable table;
    int i;


    if (!check_and_store_arguments(argc, argv, &table))
    {
        ft_putstr_fd("Error: Invalid arguments\n", 2);
        return 1;
    }
    initialize_table(&table);
    while (1)
    {
        if (is_philosopher_dead(&table)) {
            ft_detach(&table);
            return (1);
        }
    }
    for (i = 0; i < table.args->num_philosophers; i++)
    {
        pthread_mutex_destroy(&table.mutex[i]);
    }
    for (i = 0; i < table.args->num_philosophers; i++)
    {
        pthread_join(table.threads[i], NULL);
    }
    // free(table->mutex);
    // free(table->threads);
    // free(table->philosophers);

    return 0;
}
