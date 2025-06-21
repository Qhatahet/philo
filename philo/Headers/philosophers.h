/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:37 by qais              #+#    #+#             */
/*   Updated: 2025/06/21 17:37:35 by qhatahet         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t			philo;
	int					philo_id;
	int					meals;
	long				last_meal;
	pthread_mutex_t			*left;
	pthread_mutex_t			*right;
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

#endif