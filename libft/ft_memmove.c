/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:16:50 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 13:50:51 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*sr;
	char		*dest;
	size_t		i;

	i = 0;
	dest = (char *)dst;
	sr = (char *)src;
	if (dest == sr)
		return (dest);
	if (dest > sr)
	{
		while (len--)
			dest[len] = sr[len];
	}
	else
	{
		while (i < len)
		{
			dest[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
