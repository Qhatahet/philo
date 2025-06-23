/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:37 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 03:37:11 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>


/*
	philosophers as threads
	forks as mutexs
	
*/
typedef struct s_table t_table;

typedef struct s_philo
{
	pthread_t			philo;
	int					philo_id;
	int					meals;
	long				last_meal;
	pthread_mutex_t			*left;
	pthread_mutex_t			*right;
	t_table 	*table;
}			t_philo;

typedef struct s_table
{
	t_philo				**philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	
	int					philo_num;
	int					num_meals;
	int					philo_seat;
	int					flag;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	struct timeval		start;
}			t_table;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*routine(void *content);
void 	*ft_waiter(void *args);
long	ft_clock(struct timeval start);
int		check_if_anyone_died(t_philo *philo);
t_table	*allocate_init_table(char **args);
void	init_philo(t_table *table, char **arg);
void	init_mutex(t_table *table);
int		check_min_max_time(char **args);
int		validate_input(int argc, char **argv);
void	ft_usleep(t_philo *philo, long time);
void	resturant_clean_up(t_table *table);
void	print_with_check(t_philo *philo,char *s);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	pick_up_forks(t_philo *philo);
void	leave_forks(t_philo *philo);

#endif