/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:33:35 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/04 09:49:42 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	*join_all_vars(char **words, char **result)
{
	int		i;
	char	*tmp;

	i = 0;
	while (words[i])
	{
		tmp = *result;
		*result = ft_strjoin(*result, words[i]);
		if (!*result)
			return (free(tmp), free(*result), free_2d_array(words), NULL);
		free(tmp);
		i++;
	}
	return (*result);
}

int	inside_single_quotes(char *s, int i)
{
	int	quote;
	int	dquote;
	int	j;

	quote = 0;
	dquote = 0;
	j = 0;
	while (i >= j)
	{
		if (s[j] == '\'' && dquote == 0)
			quote = !quote;
		if (s[j] == '\"' && quote == 0)
			dquote = !dquote;
		j++;
	}
	if (quote)
		return (1);
	return (0);
}

int	get_quotes_count(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	j = 0;
	while (str[i])
	{
		while ((str[i] != '$' || (str[i] == '$'
					&& non_var_name((char *)str, i + 1))) && str[i])
			i++;
		j++;
		if (str[i] == '$' && inside_single_quotes(str, i) && str[i + 1] != '$')
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

int	start_expanding(char **words, int i, char **result, t_env_vars *head)
{
	while (words[i])
	{
		if (!get_extras_and_join(head, words, i))
			return (free(*result), 0);
		i++;
	}
	if (!join_all_vars(words, result))
		return (0);
	return (1);
}

char	*expand_vars(char *holder, t_t_type type, t_env_vars *head)
{
	int		i;
	char	**words;
	char	*result;

	i = 0;
	(void)type;
	result = ft_strdup("");
	if (!result)
		return (free(holder), NULL);
	// if (type == HEREDOC_TOKEN)
	words = ft_env_split_no_qt(holder, '$');
	// else
	// 	words = ft_env_split(holder, '$');
	if (!words)
		return (free(holder), free(result), NULL);
	if (!words[0])
		return (free_2d_array(words), free(result), holder);
	if (*holder != '$')
		i++;
	free(holder);
	if (!start_expanding(words, i, &result, head))
		return (NULL);
	free_2d_array(words);
	return (result);
}
