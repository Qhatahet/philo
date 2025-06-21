/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:32:05 by qais              #+#    #+#             */
/*   Updated: 2025/06/21 14:30:51 by qhatahet         ###   ########.fr       */
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

static int	numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	result(char *res, long num, int i, int len)
{
	while (len > i)
	{
		res[len - 1] = num % 10 + '0';
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nbr;
	int		i;
	int		nlen;

	i = 0;
	nlen = numlen(n);
	res = (char *)malloc(nlen + 1);
	if (!res)
		return (0);
	nbr = n;
	if (nbr < 0)
	{
		res[i] = '-';
		nbr *= -1;
		i++;
	}
	result(res, nbr, i, nlen);
	res[nlen] = '\0';
	return (res);
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
