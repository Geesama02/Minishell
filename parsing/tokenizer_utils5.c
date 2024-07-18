/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:44:22 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/18 16:24:28 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int is_redirection(t_t_type type)
{
	return (type == REDIRECTION_A || type == REDIRECTION_I || type == REDIRECTION_O);
}

int is_redirection_heredoc(char *str)
{
	return (set_token_type(str) == REDIRECTION_I
		|| set_token_type(str) == REDIRECTION_O
		|| set_token_type(str) == REDIRECTION_A
		|| set_token_type(str) == HEREDOC);
}

int	has_redirection_extras(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == ' ' && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	free_token_array(t_token_array *token_array)
{
	int	i;

	i = 0;
	while (token_array[i].token)
	{
		free(token_array[i].token);
		i++;
	}
	free(token_array);
}



int	check_redirections_extras(t_token_array *token_array)
{
	int	i;
	char	*extra;
	char	*tmp;

	i = 0;
	while (token_array[i].token)
		i++;
	while (i >= 0)
	{
		if (i > 0 && is_redirection(token_array[i].type)
			&& has_redirection_extras(token_array[i + 1].token))
		{
			extra = ft_split_first(token_array[i + 1].token);
			if (!extra)
				return (free_token_array(token_array), exit(1), 0);
			tmp = token_array[i - 1].token;
			token_array[i - 1].token = ft_strjoin(tmp, extra);
			if (!token_array[i - 1].token)
				return (free(tmp), free(extra), free_token_array(token_array), exit(1), 0);
			free(tmp);
			free(extra);
		}
		i--;
	}
	return (0);
}
