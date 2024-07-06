/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:23:20 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 20:28:22 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	z;
	char	*str1;
	char	*str2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	z = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (i < ft_strlen(s1))
		p[i++] = str1[z++];
	z = 0;
	while (i < ft_strlen(s1) + ft_strlen(s2))
		p[i++] = str2[z++];
	p[i] = '\0';
	return (p);
}
