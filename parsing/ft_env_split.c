/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:51:51 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/30 14:55:04 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c != s[i] && s[i])
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && !non_var_name((char *)s, i + 1)
			&& inside_single_quotes((char *)s, i) == 0 && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static int	count_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && (s[i] != c || (s[i] == c && non_var_name((char *)s, i + 1))
			|| (s[i] == c && inside_single_quotes((char *)s, i))))
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

static void	skip_c(char const *s, char c, int *i, int *n)
{
	*n = 0;
	while (s[*i] == c && !non_var_name((char *)s, *i + 1)
		&& inside_single_quotes((char *)s, *i) == 0)
		(*i)++;
}

char	**ft_env_split(char const *s, char c)
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
		skip_c(s, c, &i, &n);
		str[l] = (char *)malloc(count_word(s, c, i) + 1);
		if (!str[l])
			return (sec_alloc(str, l));
		while ((s[i] != c || (s[i] == c && non_var_name((char *)s, i + 1))
				|| (s[i] == c && inside_single_quotes((char *)s, i))) && s[i])
			str[l][n++] = s[i++];
		str[l++][n] = '\0';
	}
	str[l] = 0;
	return (str);
}
