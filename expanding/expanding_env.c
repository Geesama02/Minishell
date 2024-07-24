/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:02:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/24 09:32:54 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	non_var_name(char *str, int i)
{
	return (i > 0 && !ft_isalpha(str[i]) && str[i] != '_'
		&& (str[i] != '?' || ft_isalpha(str[i - 1]))
		&& (str[i] != '-' || ft_isalpha(str[i - 1]))
		&& (str[i] != '@' || ft_isalpha(str[i - 1]))
		&& !ft_isdigit(str[i]) && (str[i] != '\"' || ft_isalpha(str[i - 1]))
		&& (str[i] != '\'' || ft_isalpha(str[i - 1])));
}

char	*join_var(char **words, int i, char *env_value, char *tmp)
{
	char	*word_tmp;

	word_tmp = ft_strjoin(env_value, tmp);
	if (!word_tmp)
		return (free(tmp), free_2d_array(words), NULL);
	free(words[i]);
	return (word_tmp);
}

char	*join_var_with_extras(t_env_vars *head
	, char **words, int i, char *extras)
{
	char	*tmp;
	char	*env_value;

	tmp = ft_strdup(extras);
	if (!tmp)
		return (free_2d_array(words), NULL);
	extras[0] = '\0';
	env_value = search_for_var(head, words[i]);
	if (env_value)
	{
		words[i] = join_var(words, i, env_value, tmp);
		if (!words[i])
			return (NULL);
	}
	else
	{
		words[i] = join_var(words, i, "", tmp);
		if (!words[i])
			return (NULL);
	}
	free(tmp);
	return (*words);
}

char	*get_extras_and_join(t_env_vars *head, char **words, int i)
{
	char	*extras;
	char	*env_value;
	char	*word_tmp;

	extras = get_extra_chars(words[i]);
	if (extras)
	{
		if (!join_var_with_extras(head, words, i, extras))
			return (NULL);
	}
	else
	{
		env_value = search_for_var(head, words[i]);
		if (env_value)
		{
			word_tmp = ft_strdup(env_value);
			if (!word_tmp)
				return (free_2d_array(words), NULL);
			free(words[i]);
			words[i] = word_tmp;
		}
		else
			words[i][0] = '\0';
	}
	return (words[i]);
}

int	has_vars_no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
