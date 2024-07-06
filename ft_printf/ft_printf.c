/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:31:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/06 14:48:35 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	print_conditions(va_list args, char format, int *ptr_c)
{
	if (format == '%')
		ft_putchar('%', ptr_c);
	else if (format == 'c')
		ft_putchar(va_arg(args, int), ptr_c);
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), ptr_c);
	else if (format == 's')
		isstring(va_arg(args, char *), ptr_c);
	else if (format == 'p')
		per_p(va_arg(args, void *), ptr_c);
	else if (format == 'x' || format == 'X')
		per_x(va_arg(args, int), format, ptr_c);
	else if (format == 'u')
		ft_putnbr(va_arg(args, unsigned int), ptr_c);
	else
		ft_putchar(format, ptr_c);
}

int	ft_printf_err(const char *format, ...)
{
	va_list	args;
	int		counter;

	counter = 0;
	va_start(args, format);
	if (!format || write(2, "", 0) == -1)
		return (-1);
	while (*format)
	{
		if (*format != '%')
			ft_putchar(*format, &counter);
		if (*format == '%')
		{
			format++;
			print_conditions(args, *format, &counter);
		}
		format++;
	}
	va_end(args);
	return (counter);
}
