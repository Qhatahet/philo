/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:17:21 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 18:21:23 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	philo->last_meal = ft_clock(philo->table->start);
	if (philo->table->num_meals != -1 || philo->meals != 0)
		philo->meals--;
	if (philo->meals == 0)
		philo->table->eaten++;
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
	ft_usleep(philo, 5);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		ft_usleep(philo, 0);
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

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
