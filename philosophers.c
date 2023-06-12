/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/12 19:08:20 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long ft_time(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return time_in_ms;
}

int check_philosopher_dead(DiningTable *table)
{
    // last_meal = current_time_ms - table->last_meal_time.tv_sec * 1000 + table->last_meal_time.tv_usec / 1000;
    int i = 0;
    while (1)
        i = 0;
        while (i < table->args->num_philosophers)
        {
            printf("%ld\n", ft_time() - table->philosophers[i].last_meal);
            if (ft_time() - table->philosophers[i].last_meal > table->args->time_to_die)
            {
                table->is_philosopher_dead = 1;
                return 1;
            }
            i++;
        }

    return 0;
}

void *routine(void *arg)
{
    Philosopher *philo = (Philosopher *)arg;
    if (philo->philosopher_id % 2 != 0)
        usleep(500);
    while (1)
    {
        // if (check_philosopher_dead(philo))
        // {
        //     return NULL;
        // }
        printf("%ld %d is thinking\n",ft_time() - philo->start,  philo->philosopher_id);
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n", ft_time() - philo->start, philo->philosopher_id);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n", ft_time() - philo->start,  philo->philosopher_id);
        printf("%ld %d is eating\n",ft_time() - philo->start,  philo->philosopher_id);
        philo->last_meal = ft_time();
        usleep(philo->args->time_to_eat * 1000);
        // printf("*%d*\n", );
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        printf("%ld %d is sleeping\n",ft_time() - philo->start,  philo->philosopher_id);
        usleep(philo->args->time_to_sleep * 1000);
        // printf("*%d*\n", philo->args->time_to_sleep );

    }
    // printf("%d\n", philo->args->num_philosophers);
    return NULL;
}

void initialize_table(DiningTable *table)
{
    table->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->args->num_philosophers);
    for (int i = 0; i < table->args->num_philosophers; i++)
    {
        // table->mutex[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(&(table->mutex[i]), NULL);
    }

    int i;

    long time = ft_time();
    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * table->args->num_philosophers);
    // printf("*%d*\n", table->args->num_philosophers);
    for (i = 0; i < table->args->num_philosophers; i++)
    {
        // table->philosophers[i] = malloc(sizeof(Philosopher));
        table->philosophers[i].last_meal = time;
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
    // check_philosopher_dead(&table);
    initialize_table(&table);

    for (i = 0; i < table.args->num_philosophers; i++)
    {
        pthread_mutex_destroy(&table.mutex[i]);
    }
    for (i = 0; i < table.args->num_philosophers; i++)
    {
        pthread_join(table.threads[i], NULL);
    }
//     free(table->mutex);
//     free(table->threads);
//     free(table->philosophers);

    return 0;
}
