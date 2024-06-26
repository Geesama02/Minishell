/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:07:18 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 15:32:49 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	count_heredoc_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] != ' ' || (input[i] != ' '
				&& is_inside_quotes(input, i) == 0)) && (!is_op(input + i)
			|| (is_op(input + i) && is_inside_quotes(input, i))))
		i++;
	return (i);
}

int	has_more_cmds(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' '
			&& is_inside_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ignore_quotes(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[len] == ' ')
	{
		str[len] = '\0';
		len--;
	}
	if (str[len] == '\"' || str[len] == '\'')
		str[len] = '\0';
	while (str[i] == ' ')
		i++;
	if (str[i] == '\"' || str[i] == '\'')
		str++;
	return (str);
}

char	*ft_split_first(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != ' ' && is_inside_quotes(str, i) == 0)
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
