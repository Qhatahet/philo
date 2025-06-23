/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:36:48 by qhatahet          #+#    #+#             */
/*   Updated: 2025/06/23 22:01:59 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_anyone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->flag)
	{
		pthread_mutex_unlock(&philo->table->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->lock);
	return (0);
}

void	*routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->table->philo_num == 1)
	{
		print_with_check(philo, "has taken a fork");
		usleep(philo->table->t_die * 1000);
		return (NULL);
	}
	while (1)
	{
		if (check_if_anyone_died(philo))
			break ;
		pick_up_forks(philo);
		ft_eating(philo);
		leave_forks(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

static int	check_if_all_eaten(t_table *table)
{
	if (table->eaten == table->philo_num)
		return (1);
	return (0);
}

static int	meals(t_table *table)
{
	if (table->num_meals != -1)
	{
		if (check_if_all_eaten(table))
		{
			table->flag = 1;
			pthread_mutex_unlock(&table->lock);
			return (1);
		}
	}
	return (0);
}

void	*ft_waiter(void *args)
{
	t_table	*table;
	int		i;
	long	t_die;

	i = 0;
	table = (t_table *) args;
	t_die = table->t_die;
	while (1)
	{
		pthread_mutex_lock(&table->lock);
		if (meals(table))
			return (NULL);
		if (ft_clock(table->start) - table->philos[i]->last_meal >= t_die)
		{
			table->flag = 1;
			pthread_mutex_unlock(&table->lock);
			printf("%li %i died\n", ft_clock(table->start),
				table->philos[i]->philo_id);
			return (NULL);
		}
		pthread_mutex_unlock(&table->lock);
	}
	return (NULL);
}
