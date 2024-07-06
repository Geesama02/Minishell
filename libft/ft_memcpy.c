/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:57:36 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 17:18:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*sr;
	char	*dest;

	i = 0;
	dest = (char *)dst;
	sr = (char *)src;
	if (dest == 0 && src == 0)
		return (dest);
	while (i < n)
	{
		dest[i] = sr[i];
		i++;
	}
	return (dest);
}
