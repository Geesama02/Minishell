/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:59:03 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 13:55:27 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	int				index;
	char			*p;
	unsigned char	cc;

	i = 0;
	index = -1;
	cc = (unsigned char)c;
	while (s[i])
	{
		if ((unsigned char)s[i] == cc)
			index = i;
		i++;
	}
	p = (char *)s + index;
	if (cc == 0)
		return ((char *)s + i);
	if (index >= 0)
		return (p);
	else
		return (0);
}
