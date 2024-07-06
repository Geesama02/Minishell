/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:36:37 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 17:45:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	word_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i += 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr(char *p, int n, int *i)
{
	long	ln;

	ln = (long)n;
	if (ln < 0)
	{
		p[(*i)] = '-';
		(*i)++;
		ln = -ln;
	}
	if (ln >= 10)
		ft_putnbr(p, ln / 10, i);
	p[(*i)] = (ln % 10) + '0';
	(*i)++;
}

char	*ft_itoa(int n)
{
	size_t	z;
	size_t	length;
	int		i;
	char	*p;

	z = 0;
	i = 0;
	length = word_len(n);
	p = malloc((sizeof(char) * length) + 1);
	if (!p)
		return (0);
	ft_putnbr(p, n, &i);
	p[length] = '\0';
	return (p);
}
