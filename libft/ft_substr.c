/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:57:50 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:51:11 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alloc(size_t j, unsigned int start, size_t len)
{
	char	*str;

	if (start < j && start + len != j + 1)
		str = malloc(len + 1);
	else if (start + len == j + 1)
		str = malloc(len);
	else
		str = malloc(1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (j < len)
		len = j - start;
	str = ft_alloc(j, start, len);
	if (!str)
		return (NULL);
	while (len > i && start < j && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	if (start + len != j + 1 || s[start] == '\0')
		str[i] = '\0';
	return (str);
}
