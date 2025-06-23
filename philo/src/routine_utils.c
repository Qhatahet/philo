/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:17:21 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 03:35:57 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	philo->last_meal = ft_clock(philo->table->start);
	if (philo->table->num_meals != -1)
		philo->meals--;
	pthread_mutex_unlock(&philo->table->lock);
	print_with_check(philo, "is eating");
	ft_usleep(philo, philo->table->t_eat);
}

void	ft_sleeping(t_philo *philo)
{
	print_with_check(philo, "is sleeping");
	ft_usleep(philo, philo->table->t_sleep);
}

void	ft_thinking(t_philo *philo)
{
	print_with_check(philo, "is thinking");
}

void pick_up_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{	
		pthread_mutex_lock(philo->left);
		print_with_check(philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		print_with_check(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		print_with_check(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		print_with_check(philo, "has taken a fork");
	}
}

void leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
