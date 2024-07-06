/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:49:29 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:56 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;
	char	*dest;
	int		i;

	i = 0;
	str = (char *)src;
	dest = (char *)dst;
	if (str == NULL && dest == NULL)
		return (dst);
	while (n > 0)
	{
		dest[i] = str[i];
		i++;
		n--;
	}
	return (dst);
}
