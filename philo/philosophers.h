/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:09:50 by aet-tass          #+#    #+#             */
/*   Updated: 2023/06/16 23:03:19 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				ntpm_eat;
}					t_args;

typedef struct philosophers
{
	int				nbr_of_meals_eaten;
	int				philosopher_id;
	t_args			*args;
	int				ntpm_eat;
	pthread_t		tid;
	long			start;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	void			*table;
}					t_Philosopher;

typedef struct Diningtable
{
	t_Philosopher		*philosophers;
	pthread_mutex_t		*mutex;
	pthread_t			*threads;
	t_args				*args;
	int					is_philosopher_dead;
	int					philo_dead_id;
}					t_DiningTable;

void				ft_putstr_fd(char *s, int fd);
long				ft_time(void);
int					check_philosopher_dead(t_DiningTable *philo);
int					check_and_store_arguments(int argc, char *argv[],
						t_DiningTable *table);
int					ft_atoi(char *str);
int					ft_isdigit(int ch);
int					ft_strlen(char *str);
void				ft_sleep(int time, t_DiningTable *table);
long				ft_time(void);
void				ft_detach(t_DiningTable *table);
void				*routine(void *arg);
int					is_time_to_die(t_DiningTable *table, int p_index);
int					has_philosopher_eaten_enough(t_DiningTable *t,
						int p_index);
int					is_philosopher_dead(t_DiningTable *table);
void				initialize_mutexes(t_DiningTable *table);
void				initialize_philosophers(t_DiningTable *table);
void				initialize_threads(t_DiningTable *table);
void				initialize_table(t_DiningTable *table);

#endif
