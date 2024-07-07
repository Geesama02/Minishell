/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:56 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/15 17:46:57 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	per_x(unsigned int num, char format, int *ptr_c)
{
	int		index;
	char	hex[17];
	char	*base;
	int		z;

	z = 0;
	base = "0123456789abcdef";
	if (num == 0)
		ft_putchar('0', ptr_c);
	while (num != 0)
	{
		index = num % 16;
		if (format == 'X' && index >= 10)
			hex[z] = *(base + index) - 32;
		else
			hex[z] = *(base + index);
		num /= 16;
		z++;
	}
	while (z > 0)
	{
		ft_putchar(hex[z - 1], ptr_c);
		z--;
	}
}
