/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:21:24 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/18 22:28:49 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_mutexes(t_DiningTable *table)
{
	// int	i;

	table->mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	table->mutex_death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	table->mutex_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);

	// table->mutex = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t*)
	// 		* table->args->num_philosophers);
	// i = 0;
	// while (i < table->args->num_philosophers)
	// {
	// 	table->mutex[i] =(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// 	pthread_mutex_init((table->mutex[i]), NULL);
	// 	i++;
	// }
	pthread_mutex_init(table->mutex_print, NULL);
	pthread_mutex_init(table->mutex_death, NULL);
	pthread_mutex_init(table->mutex_meal, NULL);


}

void	initialize_philosophers(t_DiningTable *table)
{
	long	time;
	int		i;

	time = ft_time();
	table->philosophers = (t_Philosopher *)malloc(sizeof(t_Philosopher)
			* table->args->num_philosophers);
	table->mutex = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t*)
			* table->args->num_philosophers);
	table->mutex_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	table->mutex_death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	table->mutex_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(table->mutex_print, NULL);
	pthread_mutex_init(table->mutex_death, NULL);
	pthread_mutex_init(table->mutex_meal, NULL);
	i = 0;
	while (i < table->args->num_philosophers)
	{
		table->mutex[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((table->mutex[i]), NULL);
		i++;
	}
	i = 0;
	while (i < table->args->num_philosophers)
	{
		table->philosophers[i].last_meal = time;
		table->philosophers[i].nbr_of_meals_eaten = 0;
		table->philosophers[i].table = table;
		table->philosophers[i].args = table->args;
		table->philosophers[i].start = time;
		table->philosophers[i].philosopher_id = i + 1;
		table->philosophers[i].left_fork = table->mutex[i];
		table->philosophers[i].right_fork = table->mutex[(i + 1)
			% table->args->num_philosophers];
		i++;
	}
}

void	initialize_threads(t_DiningTable *table)
{
	int	i;

	table->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* table->args->num_philosophers);
	i = 0;
	while (i < table->args->num_philosophers)
	{
		pthread_create(&table->threads[i], NULL, routine,
			&table->philosophers[i]);
		pthread_detach(table->threads[i]);
		i++;
	}
}

void	initialize_table(t_DiningTable *table)
{
	// initialize_mutexes(table);
	initialize_philosophers(table);
	initialize_threads(table);
}
