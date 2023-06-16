/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 22:24:33 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char *argv[])
{
    DiningTable table;
    int i;

    if (!check_and_store_arguments(argc, argv, &table))
        return (1);
    initialize_table(&table);
    while (1)
    {
        if (is_philosopher_dead(&table))
        {
            ft_detach(&table);
            return (1);
        }
    }
    i = 0;
    while (i++ < table.args->num_philosophers)
        pthread_mutex_destroy(&table.mutex[i]);
    i = 0;
    while (i++ < table.args->num_philosophers)
        pthread_join(table.threads[i], NULL);
    return (0);
}
