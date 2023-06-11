/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/12 00:13:51 by aet-tass         ###   ########.fr       */
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

//The Philosopher struct represents an individual philosopher

typedef struct s_args
{
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_args;

typedef struct {
    //ading a variable int last_eat : inisialise au debut avec the start time( the time we joined);
    int philosopher_id;
    pthread_t tid;
    long start;
    long last_meal;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
} Philosopher;


/*
In the context of the dining philosophers problem, mutexes are used to represent the forks
on the dining table. Each philosopher needs to acquire two forks (left and right) to be able to
eat. By using mutexes, we can ensure that only one philosopher can hold a particular fork at
a time, preventing multiple philosophers from attempting to pick up the same fork
simultaneously.
*/


typedef struct {
    // adding a variable int chaeck which check if the philo died or not , it takes 0 by default and in the
    // the routine function , before doing anything we should check that int , if is died it takes 1 so we did
    // nothing

    Philosopher **philosophers;
    pthread_mutex_t **mutex;
    pthread_t    *threads;
    t_args      *args;
    int is_philosopher_dead;
} DiningTable;


void	ft_putstr_fd(char *s, int fd);
long ft_time(void);
int check_philosopher_dead(DiningTable *philo);
int check_and_store_arguments(int argc, char *argv[], DiningTable *table);
int	ft_atoi(char *str);
int	ft_isdigit(int ch);



#endif
//gcc -fsanitize=thread -g threads.c && ./a.out

