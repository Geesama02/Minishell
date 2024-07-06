/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:57:29 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 18:16:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, 
			size_t dstsize)
{
	size_t	i;
	char	*dest;
	char	*sr;

	i = 0;
	dest = (char *)dst;
	sr = (char *)src;
	while (i < dstsize - 1 && sr[i] && dstsize != 0)
	{
		dest[i] = sr[i];
		i++;
	}
	if (dstsize != 0)
		dest[i] = '\0';
	i = 0;
	while (sr[i])
		i++;
	return (i);
}
