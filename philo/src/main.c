/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:06 by qais              #+#    #+#             */
/*   Updated: 2025/06/19 20:20:45 by qhatahet         ###   ########.fr       */
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

int	init_philos(char **args)
{
	t_table	*utils;
	
	utils = malloc (sizeof(t_table *));
	if (!utils)
		return (1);
	utils->philos = malloc (sizeof(t_philo *));
	if (!utils->philos)
		return (1);
	utils->philos = NULL;
	utils->forks = malloc (sizeof(pthread_mutex_t) * ft_atoi(args[1]));
	if (!utils->forks)
		return (1);
	utils->philo_num = ft_atoi(args[1]);
	utils->t_die = ft_atoi(args[2]);
	utils->t_eat = ft_atoi(args[3]);
	utils->t_sleep = ft_atoi(args[4]);
	if (args[5])
	{
		utils->philos->meals = ft_atoi(args[5]);
		if (utils->philos->meals == 0)
		{
			printf("arg[5] invalid argument\n");
			return (1);
		}
	}
	else
		utils->philos->meals = -1;
	return (0);
}

int	validate_input(char **argv)
{
	int	i;
	int	j;

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
	if (argc == 5 || argc == 6)
	{
		if (!validate_input(argv))
			return (1);
		if (init_philos(argv))
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
