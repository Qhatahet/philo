/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resturant_clean_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:06:30 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 03:08:02 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean_up_philos(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	resturant_clean_up(t_table *table)
{
	if (table)
	{
		if (table->forks)
		{
			pthread_mutex_destroy(table->forks);
			free(table->forks);
		}
		if (table->philos)
			clean_up_philos(table->philos);
		pthread_mutex_destroy(&table->lock);
		free (table);
	}
}
