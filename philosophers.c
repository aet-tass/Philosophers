/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/10 13:39:23 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *routine(void *arg)
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
