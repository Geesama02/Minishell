/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:06 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/11 13:05:14 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	has_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	**remove_from_array(char **words, int i)
{
	int		j;
	int		k;
	char	**new;

	j = 0;
	k = 0;
	new = malloc(sizeof(char *) * (count_len(words)));
	if (!new)
		return (free_2d_array(words), NULL);
	while (words[j])
	{
		if (j != i)
		{
			new[k] = words[j];
			k++;
		}
		else
			free(words[j]);
		j++;
	}
	new[k] = NULL;
	free(words);
	return (new);
}

void	if_must_split(char ***cmds, int *n, t_token_tree *tree, char *old)
{
	int		j;
	char	**new_cmds;

	if (has_redirection_extras((*cmds)[*n]))
	{
		j = 0;
		new_cmds = ft_split_qt((*cmds)[*n], ' ');
		if (!new_cmds && errno == ENOMEM)
			return (free_2d_array(*cmds), free(old),
				ft_close(NULL, tree->head, tree), exit(1));
		while (new_cmds[j])
		{
			*cmds = realloc_tokens(*cmds, *n + j, new_cmds[j]);
			if (!*cmds)
				return (free_2d_array(new_cmds), free(old),
					ft_close(NULL, tree->head, tree), exit(1));
			j++;
		}
		free(new_cmds);
		*cmds = remove_from_array(*cmds, *n + j);
		if (!*cmds && errno == ENOMEM)
			return (free(old), ft_close(NULL, tree->head, tree), exit(1));
	}
	remove_empty(cmds, n, tree, old);
}

char	*remove_space_last(char *str)
{
	int	i;

	switch_tabs_to_spaces(str);
	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == ' ' && str[i - 1] == ' ')
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}

int	get_not_inside_qt(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && is_inside_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}
