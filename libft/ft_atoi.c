/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:55:29 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 10:16:03 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_m(const char *str, int *ptr_i)
{
	int	i;
	int	m;

	i = 0;
	m = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	*ptr_i = i;
	return (m);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		m;
	long	res;

	res = 0;
	m = check_m(str, &i);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (m == 1 && (res > 922337203685477580
				|| (res >= 922337203685477580 && str[i] > '7')))
			return (-1);
		if (m == -1 && (res > 922337203685477580
				|| (res >= 922337203685477580 && str[i] > '8')))
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(res * m));
}
