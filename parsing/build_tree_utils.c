/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:35:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/05 16:47:54 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	handle_tree_fail(t_token_tree *root)
{
	if (!root)
		return ;
	handle_tree_fail(root->left);
	handle_tree_fail(root->right);
	free(root);
}

void	handle_node_failure(t_stack *stack, t_token_tree **stack_tree,
	int tree_offset)
{
	int	i;

	i = 0;
	while (tree_offset >= 0)
	{
		handle_tree_fail(stack_tree[tree_offset]);
		tree_offset--;
	}
	while (i < stack->head)
	{
		free(stack->token[i].token);
		i++;
	}
	free(stack->token);
	free(stack);
	free(stack_tree);
}
