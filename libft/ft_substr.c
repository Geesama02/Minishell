/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:45:57 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 17:44:51 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_word(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start] && i < len)
	{
		start++;
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	i = 0;
	if (len > ft_strlen(s) && start < ft_strlen(s))
		p = malloc((sizeof(char)) * ((ft_strlen(s) - start) + 1));
	else if (start >= ft_strlen(s) || len == 0)
		p = malloc(1);
	else
		p = malloc((sizeof(char)) * ((count_word(s, start, len)) + 1));
	if (!p)
		return (0);
	while (start < ft_strlen(s) && i < (unsigned int)len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
