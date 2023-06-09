/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:39:30 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/19 16:16:47 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_sleep(int time)
{
	long	start;

	start = ft_time();
	while (ft_time() - start < time)
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

int	check_philosopher_death(t_DiningTable *table, int index)
{
	if (is_time_to_die(table, index))
	{
		mark_philosopher_as_dead(table, index);
		print_philosopher_death(table, index);
		return (1);
	}
	return (0);
}
