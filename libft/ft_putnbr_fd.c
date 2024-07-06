/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:08:32 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:53:09 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	change_long(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
		change_long(n, fd);
	}
	else if (n > 9)
	{
		change_long(n / 10, fd);
		change_long(n % 10, fd);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483647)
	{
		write(fd, "-2147483647", 11);
	}
	else
	{
		change_long(n, fd);
	}
}
