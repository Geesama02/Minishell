/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:11:02 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/11 14:44:34 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

int	handle_non_cmd(t_stack *stack, t_token_tree **stack_tree, int *tree_offset, int i)
{
	t_token_tree *tmp_right;
	t_token_tree *tmp_left;
	
	tmp_right = stack_tree[*tree_offset - 1];
	tmp_left = stack_tree[*tree_offset - 2];
	*tree_offset -= 2;
	stack_tree[*tree_offset] = create_node(stack->token[i].token, stack->token[i].type);
	stack_tree[*tree_offset]->right = tmp_right;
	stack_tree[*tree_offset]->left = tmp_left;
	(*tree_offset)++;
	return (1);
}

t_token_tree	*build_tree(t_stack *stack)
{
	int i;
	t_token_tree	**stack_tree;
	int	tree_offset;

	stack_tree = malloc(sizeof(t_token_tree *) * stack->head);
	i = 0;
	tree_offset = 0;
	while(stack->token[i].token)
	{
		if (stack->token[i].type == CMD_T)
		{
			stack_tree[tree_offset] = create_node(stack->token[i].token, CMD_T);
			tree_offset++;
		}
		else if ((stack->token[i].type == REDIRECTION_T || stack->token[i].type == OPERATOR_T)
				&& tree_offset > 1)
			handle_non_cmd(stack, stack_tree, &tree_offset, i);
		i++;
	}

	return (stack_tree[0]);
}