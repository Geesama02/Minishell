/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:05:45 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/06 17:27:45 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
	}
	free(p);
	return (NULL);
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
	if (s[i])
	{
		i++;
		j = 0;
		p[++z] = (char *)malloc(word_length2(s, i) + 1);
		while (s[i] && s[i] != ';')
			p[z][j++] = s[i++];
	}
	p[z][j] = '\0';
	p[++z] = 0;
	return (p);
}
