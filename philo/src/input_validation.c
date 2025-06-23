/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:03:28 by qais              #+#    #+#             */
/*   Updated: 2025/06/23 17:28:47 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_last_arg(char *arg)
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
		return (0);
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
