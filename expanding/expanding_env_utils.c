/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:33:35 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/21 11:57:52 by oait-laa         ###   ########.fr       */
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
	int quote;
	int dquote;
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
	int j;
	int count;

	i = 0;
	count = 0;
	j = 0;
	while (str[i])
	{
		while((str[i] != '$' || (str[i] == '$' && non_var_name((char *)str, i + 1))) && str[i])
			i++;
		j++;
		if (str[i] == '$' && inside_single_quotes(str, i) && str[i + 1] != '$')
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

// int	*get_single_quotes_position(char *str)
// {
// 	int	i;
// 	int j;
// 	int	*ints;
// 	int	l;

// 	i = 0;
// 	j = 0;
// 	l = 0;
// 	ints = malloc(sizeof(int) * (get_quotes_count(str) + 1));
// 	if (!ints)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		while((str[i] != '$' || (str[i] == '$' && non_var_name((char *)str, i + 1))) && str[i])
// 			i++;
// 		j++;
// 		if (str[i] == '$' && inside_single_quotes(str, i) && str[i + 1] != '$')
// 			ints[l++] = j;
// 		if (str[i])
// 			i++;
// 	}
// 	ints[l] = 0;
// 	return (ints);
// }

char *expand_vars(char *holder, t_t_type type, t_env_vars *head)
{
	int	i;
	char **words;
	char *result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (free(holder), NULL);
	if (type == HEREDOC_TOKEN)
		words = ft_env_split_no_qt(holder, '$');
	else
		words = ft_env_split(holder, '$');
	if (!words)
		return (free(holder), free(result), NULL);
	if (!words[0])
		return (free_2d_array(words), free(result), holder);
	if (*holder != '$')
		i++;
	free(holder);
	while (words[i])
	{
		if (!get_extras_and_join(head, words, i))
			return (free(result), NULL);
		i++;
	}
	if (!join_all_vars(words, &result))
		return (NULL);
	free_2d_array(words);
	return (result);
}

int	has_vars(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == '$' && inside_single_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

char *search_for_var(t_env_vars *head, char *env_name)
{
	t_env_vars	*tmp;

	tmp = head;
	while (tmp && ft_strcmp(tmp->env_name, env_name) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->env_val);
}
