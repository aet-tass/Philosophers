/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/19 01:23:35 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_DiningTable	*table;

	table = malloc(sizeof(t_DiningTable));
	if (!check_and_store_arguments(argc, argv, table))
		return (1);
	initialize_table(table);
	while (1)
	{
		if (is_philosopher_dead(table))
			return (1);
	}
	free(table->philosophers);
	free(table->mutex);
	free(table->threads);
	free(table->mutex_print);
	free(table->mutex_death);
	free(table->mutex_meal);
	free(table);
}
