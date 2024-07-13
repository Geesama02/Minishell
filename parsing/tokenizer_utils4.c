/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:49:36 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/13 16:22:23 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	has_multi_redirections(t_token_array *token_array)
{
	int	i;

	i = 0;
	while(token_array[i].token)
	{
		if (token_array[i + 1].token && token_array[i + 2].token && (token_array[i].type == token_array[i + 2].type)
			&& (token_array[i].type == REDIRECTION_A || token_array[i].type == REDIRECTION_I
			|| token_array[i].type == REDIRECTION_O))
			return (1);
		i++;
	}
	return (0);
}

t_token_array *find_redirection(t_token_array *token_array, t_t_type to_find, int i, int l)
{
	if (token_array[i].token)
		i++;
	while(token_array[i].token && token_array[i].type != OPERATOR_T && i < l)
	{
		if (token_array[i].type == to_find)
			return (token_array + i + 1);
		i++;
	}
	return (NULL);
}

void	swap_redirections(t_token_array *first, t_token_array *second)
{
	char *tmp;

	if (!first || !second)
		return ;
	tmp = first->token;
	first->token = second->token;
	second->token = tmp;
	first = NULL;
}

t_token_array *get_redirection(t_token_array *token_array, t_token_array *tmp, t_t_type type, int i)
{
	if (token_array[i].type == type)
		return (token_array + i + 1);
	return (tmp);
}

void switch_multi_redirections(t_token_array *token_array)
{
	int	i;
	int	l;
	t_token_array *tmp_a;
	t_token_array *tmp_i;
	t_token_array *tmp_o;

	i = 0;
	while (token_array[i].token)
	{
		l = i;
		while(token_array[i].token && token_array[i].type != OPERATOR_T)
		{
			tmp_a = get_redirection(token_array, tmp_a, REDIRECTION_A, i);
			tmp_i = get_redirection(token_array, tmp_i, REDIRECTION_I, i);
			tmp_o = get_redirection(token_array, tmp_o, REDIRECTION_O, i);
			i++;
		}
		swap_redirections(tmp_a, find_redirection(token_array, REDIRECTION_A, l, i));
		swap_redirections(tmp_i, find_redirection(token_array, REDIRECTION_I, l, i));
		swap_redirections(tmp_o, find_redirection(token_array, REDIRECTION_O, l, i));
		if (token_array[i].token)
			i++;
	}
}
