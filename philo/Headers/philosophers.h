/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:37 by qais              #+#    #+#             */
/*   Updated: 2025/06/19 20:17:49 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>


/*
	philosophers as threads
	forks as mutexs
	
*/

typedef struct s_philo
{
	pthread_t	philo;
	int			philo_id;
	int			meals;
	int			last_meal;
	int			left;
	int			right;
}			t_philo;

typedef struct s_table
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					philo_num;
	long				t_die;
	long				t_eat;
	long				t_sleep;
}			t_table;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
#endif