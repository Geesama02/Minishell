/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:05:45 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/05 16:31:53 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

static size_t	word_length(char const *s, char c, size_t i)
{
	size_t	x;

	x = 0;
	while (s[i] && s[i] != c)
	{
		x++;
		i++;
	}
	return (x);
}

static size_t	word_length2(char const *s, size_t i)
{
	size_t	x;

	x = 0;
	while (s[i] && s[i] != ';')
	{
		x++;
		i++;
	}
	return (x);
}

static void	*freeing_memory(char **p, size_t z)
{
	while (z > 0)
	{
		--z;
		free(p[z]);
		p[z] = NULL;
	}
	free(p);
	return (NULL);
}

int	fill_rest(char const *s, char **p, int i, size_t *p_z)
{
	int	j;

	j = 0;
	if (s[i])
	{
		i++;
		p[++(*p_z)] = (char *)malloc(word_length2(s, i) + 1);
		if (!p[*p_z])
			return (freeing_memory(p, *p_z), -1);
		while (s[i] && s[i] != ';')
			p[*p_z][j++] = s[i++];
		p[*p_z][j] = '\0';
	}
	return (0);
}

char	**ft_split_one(char const *s, char c)
{
	size_t	i;
	size_t	z;
	size_t	j;
	char	**p;

	if (!s)
		return (NULL);
	i = 0;
	z = 0;
	p = (char **)malloc(sizeof(char *) * 3);
	if (!p)
		return (NULL);
	p[z] = (char *)malloc(word_length(s, c, i) + 1);
	if (!p[z])
		return (freeing_memory(p, z));
	j = 0;
	while (s[i] && s[i] != c)
		p[z][j++] = s[i++];
	p[z][j] = '\0';
	if (fill_rest(s, p, i, &z) == -1)
		return (NULL);
	p[++z] = 0;
	return (p);
}
