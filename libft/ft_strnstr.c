/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:21:31 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:53:33 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		l;

	i = 0;
	l = 0;
	if (needle[0] == '\0')
		return ((char *)(haystack));
	while (len > i && haystack[i])
	{
		l = 0;
		while (haystack[i + l] == needle[l] && i + l < len)
		{
			if (needle[l + 1] == '\0')
				return ((char *)haystack + i);
			l++;
		}
		i++;
	}
	return (NULL);
}
