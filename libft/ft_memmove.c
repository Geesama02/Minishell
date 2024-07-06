/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:15:05 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/14 11:25:07 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str;
	char	*dest;

	str = (char *)src;
	dest = (char *)dst;
	if (str == NULL && dest == NULL)
		return (dst);
	if (dest < str)
	{
		while (len-- > 0)
			*dest++ = *str++;
	}
	else
	{
		while (len > 0)
		{
			*(dest + len - 1) = *(str + len - 1);
			len--;
		}
	}
	return (dst);
}
