/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:46:54 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/24 10:57:37 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	count_array(t_token_array *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
		i++;
	return (i);
}

t_stack	handle_stack_failure(t_stack *op_stack
	, t_token_array *tokens, t_stack *cmd_stack)
{
	return (free(op_stack->token),
		free_token_array(tokens), exit(1), *cmd_stack);
}
