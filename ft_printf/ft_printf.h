/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:36:29 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/14 18:46:57 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putnbr(long d, int *ptr_c);
void	ft_putchar(char c, int *ptr_c);
void	isstring(const char *string, int *ptr_c);
void	per_p(void *ptr_ul, int *ptr_c);
void	per_x(unsigned int num, char format, int *ptr_c);

#endif