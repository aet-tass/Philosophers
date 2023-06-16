/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:04:08 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 23:28:10 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argument_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (0);
	}
	return (1);
}

int	check_number_of_philosophers(int num_philosophers)
{
	if (num_philosophers <= 0)
	{
		ft_putstr_fd("Error: Invalid number of philosophers\n", 2);
		return (0);
	}
	return (1);
}

int	check_argument_values(int time_to_eat, int time_to_sleep, int time_to_die)
{
	if (time_to_eat == 0 || time_to_sleep == 0 || time_to_die == 0)
	{
		ft_putstr_fd("Error: Invalid argument\n", 2);
		return (0);
	}
	return (1);
}

int	check_and_store_arguments(int argc, char *argv[], t_DiningTable *table)
{
	table->args = malloc(sizeof(t_args));
	if (!check_argument_count(argc))
		return (0);
	table->args->num_philosophers = ft_atoi(argv[1]);
	if (!check_number_of_philosophers(table->args->num_philosophers))
		return (0);
	table->args->time_to_eat = ft_atoi(argv[3]);
	table->args->time_to_sleep = ft_atoi(argv[4]);
	table->args->time_to_die = ft_atoi(argv[2]);
	if (!check_argument_values(table->args->time_to_eat,
			table->args->time_to_sleep, table->args->time_to_die))
		return (0);
	if (argc == 6)
	{
		table->args->ntpm_eat = ft_atoi(argv[5]);
		if (table->args->ntpm_eat <= 0)
		{
			ft_putstr_fd("Error: Invalid argument\n", 2);
			return (0);
		}
	}
	else
		table->args->ntpm_eat = -1;
	return (1);
}
