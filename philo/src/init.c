/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:00:37 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 03:02:35 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_table *table, char **arg)
{
	int	i;

	i = 1;
	while (i <= ft_atoi(arg[1]))
	{
		table->philos[i - 1] = malloc(sizeof(t_philo));
		table->philos[i - 1]->philo_id = i;
		table->philos[i - 1]->last_meal = 0;
		table->philos[i - 1]->left = &table->forks[i - 1];
		table->philos[i - 1]->right = &table->forks[i % table->philo_num];
		if (arg[5])
			table->philos[i - 1]->meals = ft_atoi(arg[5]);
		else
			table->philos[i - 1]->meals = 0;
		
		table->philos[i - 1]->table = table;
		i++;
	}
}

t_table	*allocate_init_table(char **args)
{
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	table->philos = ft_calloc(sizeof(t_philo), ft_atoi(args[1]));
	if (!table->philos)
		return (NULL);
	table->forks = ft_calloc(sizeof(pthread_mutex_t), ft_atoi(args[1]));
	if (!table->forks)
		return (NULL);
	table->philo_num = ft_atoi(args[1]);
	table->t_die = ft_atoi(args[2]);
	table->t_eat = ft_atoi(args[3]);
	table->t_sleep = ft_atoi(args[4]);
	if (args[5])
		table->num_meals = ft_atoi(args[5]);
	else
		table->num_meals = -1;
	init_philo(table, args);
	return (table);
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->lock, NULL);
}
