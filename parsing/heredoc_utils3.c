/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:36:11 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/23 12:28:49 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	init_heredoc(char *delimiter, char **input, int *stdin_fd)
{
	if (!delimiter)
		return (0);
	g_is_heredoc[0] = 1;
	*stdin_fd = dup(0);
	*input = ft_strdup("");
	if (!*input)
		return (0);
	return (1);
}

void	check_between_quotes(char *str, int *i, int *count, char quote)
{
	if (str[*i])
		(*i)++;
	while (str[*i] != quote && str[*i])
	{
		(*count)++;
		(*i)++;
	}
	if (str[*i])
		(*i)++;
}

char	*ft_split_first(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (str[i] != ' '
			|| (str[i] == ' ' && is_inside_quotes(str, i))))
		i++;
	str[i] = '\0';
	tmp = ft_strdup(str + i + 1);
	return (tmp);
}

char	*handle_extra_cmd(t_token_array *token_array, char **holder,
	int *check, int i)
{
	char	*tmp;
	char	*first_cmd;
	char	*second_cmd;

	if (has_more_cmds(holder[i - 1]) && has_more_cmds(holder[i + 1]))
	{
		first_cmd = ft_split_first(token_array[i - 1].token);
		second_cmd = ft_split_first(holder[i + 1]);
		tmp = ft_strjoin(first_cmd, second_cmd);
		free(first_cmd);
		free(second_cmd);
	}
	else if (has_more_cmds(holder[i - 1]))
		tmp = ft_split_first(token_array[i - 1].token);
	else
		tmp = ft_split_first(holder[i + 1]);
	*check = 1;
	return (tmp);
}
