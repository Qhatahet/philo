/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:06 by qais              #+#    #+#             */
/*   Updated: 2025/06/22 20:35:03 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	check the number of philosophers to init the threads
	based on the number of philo init mutexes as forks

*/

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

long	ya_zenji_3arf_km_alsa3a_hassa(struct timeval start)
{
	struct timeval 		current;
	long time;
	
	gettimeofday(&current,NULL);
	time = (current.tv_sec - start.tv_sec) * 1000;
	time += (current.tv_usec - start.tv_usec) / 1000;
	return (time);
}


void	joining(t_table *table)
{
	int  i = 0;
	while (i < table->philo_num)
	{
		pthread_join(table->philos[i]->philo, NULL);
		i++;
	}
}

void	init_threads(t_table *table)
{
	int 			i;
	pthread_t monitor;

	pthread_create(&monitor, NULL, &ft_waiter, (void *)table);
	table->philo_seat = 0;
	i = 0;
	while (i != table->philo_num)
	{
		if(pthread_create(&table->philos[i]->philo, NULL, &routine, (void *)table->philos[i]) == -1)
			break;
		i++;
		usleep(100);
	}
	pthread_join(monitor,NULL);
	joining(table);
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

int	check_last_arg(char *arg)
{
	if (ft_atoi(arg) == 0)
	{
		printf("arg[5] invalid argument\n");
		return (1);
	}	
	return (0);
}

int	validate_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 6 && check_last_arg(argv[5]))
		return(0);
	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("USAGE: ./philo NUM_PHILO T_DIE");
				printf(" T_EAT T_SLEEP (optional)N_MEALS\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_min_max_time(char **args)
{
	if (ft_atoi(args[2]) < 60 || ft_atoi(args[2]) > 2147483647)
	{
		printf("invalid time argv[2]\n");
		return (0);
	}
	if (ft_atoi(args[3]) < 60 || ft_atoi(args[3]) > 2147483647)
	{
		printf("invalid time argv[3]\n");
		return (0);
	}
	if (ft_atoi(args[4]) < 60 || ft_atoi(args[4]) > 2147483647)
	{
		printf("invalid time argv[4]\n");
		return (0);
	}
	return (1);
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
	return (0);
}
