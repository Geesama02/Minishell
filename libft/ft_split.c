/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:05:45 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 10:16:20 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char const c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

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

static void	equal(char const *s, char c, size_t *ptr_i)
{
	while (s[(*ptr_i)] && s[(*ptr_i)] == c)
		(*ptr_i)++;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	z;
	size_t	j;
	char	**p;

	if (!s)
		return (NULL);
	i = 0;
	z = 0;
	p = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!p)
		return (NULL);
	while (z < count_words(s, c))
	{
		equal(s, c, &i);
		p[z] = (char *)malloc(word_length(s, c, i) + 1);
		if (!p[z])
			return (freeing_memory(p, z));
		j = 0;
		while (s[i] && s[i] != c)
			p[z][j++] = s[i++];
		p[z++][j] = '\0';
	}
	p[z] = 0;
	return (p);
}
