/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:39:30 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 22:55:58 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_sleep(int time, t_DiningTable *table)
{
	long	start;

	start = ft_time();
	while (ft_time() - start < time && !table->is_philosopher_dead)
		usleep(500);
}

long	ft_time(void)
{
	struct timeval	current_time;
	long			time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_in_ms);
}

void	ft_detach(t_DiningTable *table)
{
	int	i;

	i = 0;
	while (i < table->args->num_philosophers)
	{
		pthread_detach(table->threads[i]);
		i++;
	}
	i = 0;
	while (i < table->args->num_philosophers)
	{
		pthread_mutex_destroy(&table->mutex[i]);
		i++;
	}
}
