/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:05:45 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/24 10:47:44 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static size_t	word_length(char const *s, char c, size_t i)
{
	size_t	x;

	x = 0;
	while (s[i] && s[i] != c && s[i] != ';')
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

int	fill_rest(char const *s, char c, char **p, int j)
{
	int	i;
	int	z;

	i = 0;
	z = 1;
	if (s[i])
	{
		i++;
		i = 0;
		p[z] = (char *)malloc(word_length(s, c, i) + 1);
		if (!p[z])
			return (-1);
		while (s[j] && s[j] != ';')
			p[z][i++] = s[j++];
	}
	p[z][i] = '\0';
	p[++z] = 0;
	return (0);
}

void	first_fill(size_t *p_j, char **p, char const *s, char c)
{
	int	z;

	z = 0;
	while (s[*p_j] && s[*p_j] != c)
	{
		p[z][*p_j] = s[*p_j];
		(*p_j)++;
	}
}

char	**ft_split_one(char const *s, char c)
{
	size_t	z;
	size_t	j;
	char	**p;

	if (!s)
		return (NULL);
	z = 0;
	j = 0;
	p = (char **)malloc(sizeof(char *) * 3);
	if (!p)
		return (NULL);
	p[z] = (char *)malloc(word_length(s, c, j) + 1);
	if (!p[z])
		return (freeing_memory(p, z));
	first_fill(&j, p, s, c);
	p[z][j] = '\0';
	if (s[j] == c)
	{
		if (fill_rest(s, c, p, j) == -1)
			return (NULL);
	}
	return (p);
}
