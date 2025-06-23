/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:06 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 17:32:00 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	check the number of philosophers to init the threads
	based on the number of philo init mutexes as forks

*/

long	ft_clock(struct timeval start)
{
	struct timeval	current;
	long			time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec - start.tv_sec) * 1000;
	time += (current.tv_usec - start.tv_usec) / 1000;
	return (time);
}

void	joining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_join(table->philos[i]->philo, NULL);
		i++;
	}
}

void	init_threads(t_table *table)
{
	int			i;
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &ft_waiter, (void *)table);
	table->philo_seat = 0;
	i = 0;
	while (i != table->philo_num)
	{
		if (pthread_create(&table->philos[i]->philo, NULL,
				&routine, (void *)table->philos[i]) == -1)
			break ;
		i++;
	}
	pthread_join(monitor, NULL);
	joining(table);
}

t_table	*init_table(char **args)
{
	t_table	*table;

	table = allocate_init_table(args);
	if (!table)
		return (NULL);
	gettimeofday(&table->start, NULL);
	init_mutex(table);
	init_threads(table);
	return (table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		if (!check_min_max_time(argv))
			return (1);
		if (!validate_input(argc, argv))
			return (1);
		table = init_table(argv);
		if (!table)
			return (1);
	}
	else
	{
		printf("USAGE: ./philo NUM_PHILO T_DIE");
		printf(" T_EAT T_SLEEP (optional)N_MEALS\n");
		return (1);
	}
	resturant_clean_up(table);
	return (0);
}
