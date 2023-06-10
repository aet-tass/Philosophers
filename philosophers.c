/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c       ########    ## #     ##    ##             ## ##     */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/   ########    ##      # #    ##    ##  ##           ##    */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*void *routine(void *arg)
{
	Philosopher *philo = (Philosopher *)arg;
	if (philo->philosopher_id % 2 != 0)
		// usleep(10000);
	while (1)
	{
		// add a function print because we need to check if a philo is died 
		printf("%d philo is thinking \n", philo->philosopher_id);
		printf("%d philo has taken a fork \n", philo->philosopher_id);
		pthread_mutex_lock(philo->left_fork);
		printf("%d philo has taken a fork \n", philo->philosopher_id);
		pthread_mutex_lock(philo->left_fork);
		printf("%d philo is eating \n", philo->philosopher_id);
		// usleep(200 * 1000);  creete a function ft_sleep just adding a while check if not arriving in the exacte time
		printf("%d philo is slepping \n", philo->philosopher_id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->left_fork);
		//ti_eat = get_time(): get_time had the gettimeofday;
		// usleep(200 * 100);
		//slep(df, &check); this function i should make it that sleep and also check the value of check.
	}

	return (NULL);
}

int	main()
{
	DiningTable Dining_Table;
	Dining_Table.mutex = malloc(sizeof(pthread_mutex_t) * 5);
	Dining_Table.threads = malloc(sizeof(pthread_t) * 5);
	Dining_Table.philosophers = malloc(sizeof(Philosopher) * 5);

	int	 i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&Dining_Table.mutex[i], NULL);
		i++;
	}

	i = 0;
	while (i < 5)
	{
		Dining_Table.philosophers[i].philosopher_id = i + 1 ;
		// filing all the args ex time_to_die ......

		Dining_Table.philosophers[i].left_fork = &Dining_Table.mutex[i];
		Dining_Table.philosophers[i].right_fork = &Dining_Table.mutex[(i + 1) % 5];
		pthread_create(&Dining_Table.threads[i], NULL, &routine, &Dining_Table.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_mutex_destroy(&Dining_Table.mutex[i]);
		i++;
	}

	i = 0;
	while (i < 5)
	{
		Dining_Table.philosophers[i].philosopher_id = i + 1 ;
		pthread_join(Dining_Table.threads[i], NULL);
		i++;
	}

}

int main(int argc, char *argv[])
{
    DiningTable table;

    if (!check_and_store_arguments(argc, argv, &table))
    {
        // Arguments checking failed, exit the program
        return 1;
    }

    // Continue with the program logic using the stored arguments in the 'table' variable

    return 0;
}
*/

#include "philosophers.h"
#include <sys/time.h>

long ft_time(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return time_in_ms;
}

int check_philosopher_dead(Philosopher *philo)
{
    long current_time_ms = ft_time();
    long time_since_last_meal = current_time_ms - philo->last_meal_time.tv_sec * 1000 + philo->last_meal_time.tv_usec / 1000;

    if (time_since_last_meal > philo->time_to_die)
    {
        philo->is_philosopher_dead = 1;
        return 1;
    }

    return 0;
}
void *routine(void *arg)
{
    Philosopher *philo = (Philosopher *)arg;
    if (philo->philosopher_id % 2 != 0)
        // usleep(10000);
    while (1)
    {
        // Check if the philosopher is dead
        if (check_philosopher_dead(philo))
        {
            // Philosopher is dead, do nothing
            return NULL;
        }

        printf("%d philo is thinking\n", philo->philosopher_id);
        printf("%d philo has taken a fork\n", philo->philosopher_id);
        pthread_mutex_lock(philo->left_fork);
        printf("%d philo has taken a fork\n", philo->philosopher_id);
        pthread_mutex_lock(philo->right_fork);
        printf("%d philo is eating\n", philo->philosopher_id);
        // ft_sleep(philosopher->time_to_eat);
        printf("%d philo is sleeping\n", philo->philosopher_id);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        // time_since_last_meal = ft_time();
        // ft_sleep(philosopher->time_to_sleep);
        // check_philosopher_dead(philo);
    }

    return NULL;
}
>
void initialize_table(DiningTable *table)
{
    table->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
    table->threads = (pthread_t*)malloc(sizeof(pthread_t) * table->num_philosophers);
    table->philosophers = (Philosopher*)malloc(sizeof(Philosopher) * table->num_philosophers);

    int i;
    for (i = 0; i < table->num_philosophers; i++)
    {
        pthread_mutex_init(&(table->mutex[i]), NULL);

        Philosopher *philosopher = &(table->philosophers[i]);
        philosopher->philosopher_id = i + 1;
        philosopher->time_to_die = table->time_to_die;
        philosopher->time_to_eat = table->time_to_eat;
        philosopher->time_to_sleep = table->time_to_sleep;
        philosopher->number_of_times_each_philosopher_must_eat = table->number_of_times_each_philosopher_must_eat;
        philosopher->left_fork = &(table->mutex[i]);
        philosopher->right_fork = &(table->mutex[(i + 1) % table->num_philosophers]);
        pthread_create(&(table->threads[i]), NULL, &routine, philosopher);
    }
}

int main(int argc, char *argv[])
{
    DiningTable table;

    if (!check_and_store_arguments(argc, argv, &table))
    {
        ft_putstr_fd("Error: Invalid arguments\n", 2);
        return 1;
    }

    initialize_table(&table);

    int i;
    for (i = 0; i < table.num_philosophers; i++)
    {
        pthread_join(table.threads[i], NULL);
    }

    for (i = 0; i < table.num_philosophers; i++)
    {
        pthread_mutex_destroy(&(table.mutex[i]));
    }

    free(table.mutex);
    free(table.threads);
    free(table.philosophers);

    return 0;
}

