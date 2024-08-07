/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:49:36 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/04 15:55:25 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

t_token_array	*find_redirection(t_token_array *token_array
	, t_t_type to_find, int i, int l)
{
	if (token_array[i].token)
		i++;
	while (token_array[i].token && token_array[i].type != OPERATOR_T
		&& i < l && token_array[i].type != PARETHESIS_C)
	{
		if (token_array[i].type == to_find)
			return (token_array + i + 1);
		i++;
	}
	return (NULL);
}

t_token_array	*find_redirection_double(t_token_array *token_array
	, int i, int l)
{
	while (token_array[i].token && token_array[i].type != OPERATOR_T && i < l
		&& token_array[i].type != PARETHESIS_C)
	{
		if (token_array[i].type == REDIRECTION_A
			|| token_array[i].type == REDIRECTION_O)
			return (token_array + i + 1);
		i++;
	}
	return (token_array);
}

void	swap_redirections(t_token_array *first, t_token_array *second)
{
	char		*tmp;
	t_t_type	type_tmp;

	if (!first || !second)
		return ;
	type_tmp = first->type;
	tmp = first->token;
	first->token = second->token;
	first->type = second->type;
	second->token = tmp;
	second->type = type_tmp;
	first = NULL;
}

t_token_array	*get_redirection(t_token_array *token_array
	, t_token_array *tmp, t_t_type type, t_t_type type2)
{
	if (token_array->type == type || token_array->type == type2)
		return (token_array + 1);
	return (tmp);
}

void	switch_multi_redirections(t_token_array *token_array)
{
	int				i;
	int				l;
	t_token_array	*tmp_a_o;
	t_token_array	*tmp_i;

	i = 0;
	while (token_array[i].token)
	{
		l = i;
		tmp_a_o = NULL;
		tmp_i = NULL;
		while (token_array[i].token && token_array[i].type != OPERATOR_T
			&& token_array[i].type != PARETHESIS_C)
		{
			set_redirections(&token_array[i], &tmp_a_o, &tmp_i);
			i++;
		}
		swap_redirection_op(tmp_a_o, i, l, token_array);
		swap_redirections(tmp_a_o, find_redirection_double(token_array, l, i));
		swap_redirections(tmp_i,
			find_redirection(token_array, REDIRECTION_I, l, i));
		if (token_array[i].token)
			i++;
	}
}
