/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:19:34 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/27 11:53:34 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	set_redirections(t_token_array *token_array
	, t_token_array **tmp_a_o, t_token_array **tmp_i)
{
	*tmp_a_o = get_redirection(token_array, *tmp_a_o,
			REDIRECTION_A, REDIRECTION_O);
	*tmp_i = get_redirection(token_array, *tmp_i,
			REDIRECTION_I, REDIRECTION_I);
}

int	get_to_last_token(t_token_array *token_array)
{
	int	i;

	i = 0;
	while (token_array[i].token)
		i++;
	if (i > 0)
		i--;
	return (i);
}

int	check_for_wildcard(t_token_array *token_array, t_env_vars *head)
{
	int	i;

	i = 0;
	while (token_array[i].token)
	{
		if (has_wildcard(token_array[i].token))
		{
			if (i > 0 && handle_wildcard(&token_array[i].token,
					token_array[i - 1].token, head) == 0)
			{
				if (errno == ENOMEM)
					return (free_token_array(token_array), exit(1), 0);
				return (free_token_array(token_array), 0);
			}
			else if (i == 0 && handle_wildcard(&token_array[i].token, "", head) == 0)
			{
				if (errno == ENOMEM)
					return (free_token_array(token_array), exit(1), 0);
				return (free_token_array(token_array), 0);
			}
		}
		i++;
	}
	return (1);
}

void	init_token_vars(t_token_vars *vars, t_env_vars *head)
{
	vars->l = 0;
	vars->x = -1;
	vars->check = 0;
	vars->head = head;
}

char	*return_type(int dquote, int quote, int parenthesis)
{
	if (dquote)
		return ("\"");
	if (quote)
		return ("\'");
	if (parenthesis)
		return ("(");
	return (NULL);
}
