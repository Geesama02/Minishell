/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:51:51 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:53:14 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

static int	is_inside_quotes(char const *s, int i, char c)
{
	int	inside;

	inside = 0;
	while (i >= 0)
	{
		if (s[i] == c)
			inside = !inside;
		i--;
	}
	return (inside);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c != s[i] && s[i] && !is_inside_quotes(s, i, '\'') && !is_inside_quotes(s, i, '\"'))
		count++;
	while (s[i])
	{
		// if (s[i] == c)
		// {
		// 	printf("s[i]: %d|\n", s[i] == c);
		// 	printf("s[i + 1]: %d|\n", s[i + 1] != c);
		// 	printf("s[i + 1]: %d|\n", s[i + 1] == 0);
		// 	printf("is_inside_quotes: %d\n", !is_inside_quotes(s, i, '\''));
		// 	printf("is_inside_quotes: %d\n", !is_inside_quotes(s, i, '\"'));
		// 	printf("cond: %d\n", s[i] == c && s[i + 1] && s[i + 1] != c && !is_inside_quotes(s, i, '\'') && !is_inside_quotes(s, i, '\"'));
		// }
		if (s[i] == c && s[i + 1] && s[i + 1] != c && !is_inside_quotes(s, i, '\'') && !is_inside_quotes(s, i, '\"'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static int	count_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && (s[i] != c || (s[i] == c && is_inside_quotes(s, i, '\"'))
			|| (s[i] == c && is_inside_quotes(s, i, '\''))))
	{
		len++;
		i++;
	}
	return (len);
}

static void	*sec_alloc(char **bigstr, int l)
{
	while (l > 0)
	{
		l--;
		free(bigstr[l]);
	}
	free(bigstr);
	return (NULL);
}

static void	skip_c(char const *s, char c, int *i)
{
	while (s[*i] == c && s[*i] && !is_inside_quotes(s, *i, '\'') && !is_inside_quotes(s, *i, '\"'))
		(*i)++;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		l;
	int		n;
	char	**str;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (l < count_words(s, c))
	{
		n = 0;
		skip_c(s, c, &i);
		str[l] = (char *)malloc(count_word(s, c, i) + 1);
		if (!str[l])
			return (sec_alloc(str, l));
		while (s[i] && (s[i] != c || (s[i] == c && is_inside_quotes(s, i, '\"'))
				|| (s[i] == c && is_inside_quotes(s, i, '\''))))
			str[l][n++] = s[i++];
		str[l++][n] = '\0';
	}
	str[l] = 0;
	return (str);
}
