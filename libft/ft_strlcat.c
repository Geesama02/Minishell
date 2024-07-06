/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:39:39 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:50:38 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, 
		const char *src, size_t dstsize)
{
	int		i;
	size_t	j; 
	int		l;

	i = 0;
	j = 0;
	l = 0;
	l = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (l);
	j = ft_strlen(dst);
	if (dstsize > j)
	{
		while (src[i] && dstsize - 1 > j)
		{
			dst[j + i] = src[i];
			i++;
			dstsize--;
		}
		dst[j + i] = '\0';
		return (j + l);
	}
	else
		return (l + dstsize);
}
