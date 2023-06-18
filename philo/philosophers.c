/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/18 22:45:34 by aet-tass         ###   ########.fr       */
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
}
