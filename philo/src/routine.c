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

void	ft_usleep(t_philo *philo, long time)
{
	long time_when_start;
	long time_to_stop;
	long time_now;

	time_when_start = ya_zenji_3arf_km_alsa3a_hassa(philo->table->start);
	time_to_stop = time_when_start + time;
	while (1)
	{
		time_now = ya_zenji_3arf_km_alsa3a_hassa(philo->table->start);
		if (check_if_anyone_died(philo))
			break;
		if (time_to_stop < time_now)
			break ;
		usleep(1);
	}
}

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

void print_with_check(t_philo *philo,char *s)
{
	pthread_mutex_lock(&philo->table->lock);
	if (!philo->table->flag)
		printf("%li %i %s\n", ya_zenji_3arf_km_alsa3a_hassa(philo->table->start), philo->philo_id, s);
	pthread_mutex_unlock(&philo->table->lock);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	philo->last_meal = ya_zenji_3arf_km_alsa3a_hassa(philo->table->start);
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

void ft_take_forks(t_philo *philo)
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
void ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*routine(void *content)
{
	t_table *table;
	t_philo *philo;
	
	philo = (t_philo *)content;
	table = philo->table;
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
		ft_take_forks(philo);
		ft_eating(philo);
		ft_leave_forks(philo);
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
		if(ya_zenji_3arf_km_alsa3a_hassa(table->start) - table->philos[i]->last_meal >= table->t_die)
		{
			table->flag = 1;
			pthread_mutex_unlock(&table->lock);
			printf("%li %i died\n",ya_zenji_3arf_km_alsa3a_hassa(table->start),table->philos[i]->philo_id);
			return (NULL);
		}
		pthread_mutex_unlock(&table->lock);
	}
	return (NULL);
}