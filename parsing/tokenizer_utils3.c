/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:03:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/28 16:09:54 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	*handle_other_tokens(t_token_array *token_array, char **holder, int *i, t_token_vars *vars)
{
	if (vars->x != -1)
	{
		vars->l++;
		vars->x = -1;
		vars->check = 0;
	}
	token_array[vars->l].token = ft_strdup(holder[*i]);
	if (!token_array[vars->l].token)
		return (free_token_holder(holder, token_array, vars->l), free(vars->input), exit(1), NULL);
	token_array[vars->l].type = set_token_type(holder[*i]);
	free(holder[*i]);
	(*i)++;
	vars->l++;
	return (NULL);
}
