/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:51:02 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/14 11:25:20 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static void	check_sign(char str, int *neg, long *i)
{
	if (str == '-' || str == '+')
	{
		if (str == '-')
			*neg = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	long	i;
	long	r;
	int		neg;

	i = 0;
	r = 0;
	neg = 1;
	while (check_space(str[i]))
		i++;
	check_sign(str[i], &neg, &i);
	while (str[i])
	{
		if (neg == 1 && (r > 922337203685477580 || 
				(r >= 922337203685477580 && str[i] >= '8')))
			return (-1);
		else if (neg == -1 && (r > 922337203685477580 || 
				(r >= 922337203685477580 && str[i] >= '8')))
			return (0);
		if (str[i] >= 48 && str[i] <= 57)
			r = r * 10 + (str[i] - 48);
		else
			return (r * neg);
		i++;
	}
	return ((int)(r * neg));
}

