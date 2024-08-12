/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:44:22 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/12 16:07:27 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	is_redirection(t_t_type type)
{
	return (type == REDIRECTION_A || type == REDIRECTION_I
		|| type == REDIRECTION_O);
}

int	is_redirection_heredoc(char *str)
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
		if (str[i + 1] && str[i] == ' ' && str[i + 1] != ' '
			&& is_inside_quotes(str, i) == 0)
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

int	check_redirections_extras(char **holder)
{
	int	i;

	i = get_to_last_token(holder);
	while (i >= 0)
	{
		if (i > 0 && is_redirection_heredoc(holder[i])
			&& has_redirection_extras(holder[i + 1]))
		{
			if (holder[i - 1] && holder[i - 1][0] == ')')
			{
				print_err("Minishell: syntax error near unexpected token `",
					get_second_cmd(holder[i + 1]), "' \n");
				return (0);
			}
			join_extra_with_redi(holder, i);
		}
		i--;
	}
	return (1);
}
