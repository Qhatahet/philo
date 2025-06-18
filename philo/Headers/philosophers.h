/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:37 by qais              #+#    #+#             */
/*   Updated: 2025/06/09 11:54:57 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_state
{
	HUNGRY,
	DEAD,
}			t_state;

typedef struct s_philo
{
	pthread_t	philo;
	int			philo_num;
	t_state		state;
}			t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
#endif