/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:32:05 by qais              #+#    #+#             */
/*   Updated: 2025/06/22 17:41:13 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*p;

	p = malloc (nmemb * size);
	if (!p)
		return (NULL);
	memset(p, '\0', nmemb * size);
	return (p);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	char	*num;
	int		res;
	int		sign;

	sign = 1;
	res = 0;
	num = (char *)nptr;
	while (*num == ' ' || (*num >= 9 && *num <= 13))
		num++;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
		{
			sign *= -1;
			num++;
		}
		else
			num++;
	}
	while (*num >= '0' && *num <= '9')
	{
		res = (res * 10) + (*num - '0');
		num++;
	}
	return (res * sign);
}
