/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:19:34 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/12 12:57:11 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	get_to_last_token(char **holder)
{
	int	i;

	i = 0;
	while (holder[i])
		i++;
	if (i > 0)
		i--;
	return (i);
}

int	check_for_wildcard(t_token_tree *tree)
{
	if (has_wildcard(tree->token))
	{
		if (handle_wildcard(&tree->token, "", *tree->head) == 0
			&& errno == ENOMEM)
			return (0);
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
