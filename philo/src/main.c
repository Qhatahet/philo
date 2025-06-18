/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:59:06 by qais              #+#    #+#             */
/*   Updated: 2025/06/09 16:28:05 by qais             ###   ########.fr       */
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

void	init_philos(char *str)
{
	t_philo	philos;
	int		i;

	i = 1;
	philos.philo_num = ft_atoi(str);
	while (i <= philos.philo_num)
	{
		printf("%d\n", i);
		pthread_create(&philos.philo, NULL, routine, ft_itoa(i));
		pthread_join(philos.philo, NULL);
		i++;
		usleep(3000);
	}
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
	struct timeval	start, end;
	gettimeofday(&start, NULL);
	for (int i = 0; i < 5; i++)
		printf("qais\n");
	gettimeofday(&end, NULL);
	long seconds = end.tv_sec - start.tv_sec;
	long useconds = end.tv_usec - start.tv_usec;
	long total_microseconds = seconds * 1000000 + useconds;
	printf("Elapsed time: %ld microseconds\n", total_microseconds);
	if (argc == 5 || argc == 6)
	{
		if (!validate_input(argv))
			return (1);
		init_philos(argv[1]);
	}
	else
	{
		printf("USAGE: ./philo NUM_PHILO T_DIE");
		printf(" T_EAT T_SLEEP (optional)N_MEALS\n");
		return (1);
	}
	return (0);
}
