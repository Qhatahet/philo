/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:36:48 by qhatahet          #+#    #+#             */
/*   Updated: 2025/06/22 19:12:26by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_if_anyone_died(t_philo *philo)
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
	t_table *table;
	t_philo *philo;
	
	philo = (t_philo *)content;
	table = philo->table;
	(void)table;
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

int check_if_all_eaten(t_table *table)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < table->philo_num)
	{
		if (table->philos[i]->meals > 0)
		{
			flag = 0;
			break ;
		}
		flag = 1;
		i++;
	}
	return (flag);
}

void 	*ft_waiter(void *args)
{
	t_table *table;
	int		i;
	
	i = 0;
	table = (t_table *) args;
	while(1)
	{
		pthread_mutex_lock(&table->lock);
		if (table->num_meals != -1)
		{
			if (check_if_all_eaten(table))
			{
				table->flag = 1;
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
		}
		if(ft_clock(table->start) - table->philos[i]->last_meal >= table->t_die)
		{
			table->flag = 1;
			pthread_mutex_unlock(&table->lock);
			printf("%li %i died\n", ft_clock(table->start), table->philos[i]->philo_id);
			return (NULL);
		}
		pthread_mutex_unlock(&table->lock);
	}
	return (NULL);
}
