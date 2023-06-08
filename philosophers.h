/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/08 17:56:39 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>


//The Philosopher struct represents an individual philosopher

typedef struct {
    //ading a variable int last_eat : inisialise au debut avec the start time( the time we joined);
    int philosopher_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
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
    int num_philosophers;
    Philosopher *philosophers;
    pthread_mutex_t *mutex;
    pthread_t    *threads;
} DiningTable;

#endif
