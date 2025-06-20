/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:06 by qais              #+#    #+#             */
/*   Updated: 2025/06/20 17:36:32 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	check the number of philosophers to init the threads
	based on the number of philo init mutexes as forks

*/

void	*routine(void *content)
{
	char	*num;

	num = (char *)content;
	printf("philo %i is eating\n", ft_atoi(num));
	free(num);
	return (NULL);
}

t_table	*allocate_init_table(char **args)
{
	t_table	*table;

	table = malloc(sizeof(t_table *));
	if (!table)
		return (NULL);
	table = NULL;
	table->philos = ft_calloc(sizeof(t_philo), ft_atoi(args[1]));
	if (!table->philos)
		return (NULL);
	table->philos = NULL;
	table->forks = ft_calloc(sizeof(pthread_mutex_t), ft_atoi(args[1]));
	if (!table->forks)
		return (NULL);
	table->forks = NULL;
	table->philo_num = ft_atoi(args[1]);
	table->t_die = ft_atoi(args[2]);
	table->t_eat = ft_atoi(args[3]);
	table->t_sleep = ft_atoi(args[4]);
	if (args[5])
		table->philos->meals = ft_atoi(args[5]);
	else
		table->philos->meals = -1;
	return (table);
}

t_table	*init_table(char **args)
{
	t_table	*table;

	table = allocate_init_table(args);
	if (!table)
		return (NULL);
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

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
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
