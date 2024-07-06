/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:31:38 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/15 17:48:04 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	per_p(void *ptr_ul, int *ptr_c)
{
	int				index;
	char			hex[17];
	char			*base;
	int				z;
	unsigned long	ul;

	z = 0;
	base = "0123456789abcdef";
	ul = (unsigned long)ptr_ul;
	ft_putchar('0', ptr_c);
	ft_putchar('x', ptr_c);
	if (ul == 0)
		ft_putchar('0', ptr_c);
	while (ul != 0)
	{
		index = ul % 16;
		hex[z] = *(base + index);
		ul /= 16;
		z++;
	}
	while (z > 0)
	{
		ft_putchar(hex[z - 1], ptr_c);
		z--;
	}
}
