/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:24:17 by maglagal          #+#    #+#             */
/*   Updated: 2023/12/01 12:07:15 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*ptr;

	i = 0;
	s1_len = ft_strlen(s1);
	ptr = malloc(s1_len + 1);
	if (!ptr)
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	z;
	size_t	s2_len;
	size_t	s1_len;
	char	*p;

	i = 0;
	z = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (!p)
		return (NULL);
	while (i < s1_len)
		p[i++] = s1[z++];
	z = 0;
	while (i < s1_len + s2_len)
		p[i++] = s2[z++];
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;
	char			*p;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == cc)
		{
			p = (char *)s + i;
			return (p);
		}
		else
			i++;
	}
	if (cc == '\0')
		return ((char *)s + i);
	return (0);
}

void	terminating_string(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	buffer[i + 1] = '\0';
}
