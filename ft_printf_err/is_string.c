/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:33:30 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/14 20:16:23 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	isstring(const char *string, int *ptr_c)
{
	if (string == 0)
	{
		isstring("(null)", ptr_c);
		return ;
	}
	while (*string != 0)
		ft_putchar(*string++, ptr_c);
}
