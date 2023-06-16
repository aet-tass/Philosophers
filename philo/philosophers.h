/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 19:23:32 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>


typedef struct s_args
{
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_args;

typedef struct {
    int nbr_of_meals_eaten;
    int philosopher_id;
    t_args  *args;
    int number_of_times_each_philosopher_must_eat;
    pthread_t tid;
    long start;
    long last_meal;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
    void *table;
} Philosopher;

typedef struct {

    Philosopher *philosophers;
    pthread_mutex_t *mutex;
    pthread_t    *threads;
    t_args         *args;
    int is_philosopher_dead;
    int philo_dead_id;
} DiningTable;

void	ft_putstr_fd(char *s, int fd);
long ft_time(void);
int check_philosopher_dead(DiningTable *philo);
int check_and_store_arguments(int argc, char *argv[], DiningTable *table);
int	ft_atoi(char *str);
int	ft_isdigit(int ch);
int	ft_strlen(char	*str);

#endif
