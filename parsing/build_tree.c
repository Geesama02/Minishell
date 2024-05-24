/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:11:02 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/24 11:37:29 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void set_ids(t_token_tree *root, int *id)
{
	if (!root)
		return ;
	if (root->type == CMD_T)
	{
		root->id = *id;
		(*id)++;
	}
	else
		root->id = -1;
	set_ids(root->left, id);
	set_ids(root->right, id);
}

void set_count(t_token_tree *root, int count)
{
	if (!root)
		return ;
	root->cmd_count = count - 1;
	set_count(root->left, count);
	set_count(root->right, count);
}

int	handle_non_cmd(t_token_array token, t_token_tree **stack_tree, int *tree_offset, char **envp)
{
	t_token_tree *tmp_right;
	t_token_tree *tmp_left;
	
	tmp_right = stack_tree[*tree_offset - 1];
	tmp_left = stack_tree[*tree_offset - 2];
	*tree_offset -= 2;
	stack_tree[*tree_offset] = create_node(token.token, token.type, envp);
	stack_tree[*tree_offset]->right = tmp_right;
	stack_tree[*tree_offset]->left = tmp_left;
	(*tree_offset)++;
	return (1);
}

t_token_tree	*build_tree(t_stack *stack, char **envp)
{
	int i;
	t_token_tree	**stack_tree;
	t_token_tree	*root;
	int	tree_offset;

	stack_tree = malloc(sizeof(t_token_tree *) * stack->head);
	i = 0;
	tree_offset = 0;
	while (stack->token[i].token)
	{
		if (stack->token[i].type == CMD_T)
		{
			stack_tree[tree_offset] = create_node(stack->token[i].token, CMD_T, envp);
			tree_offset++;
		}
		else if ((stack->token[i].type == REDIRECTION_I
			|| stack->token[i].type == REDIRECTION_A || stack->token[i].type == REDIRECTION_O || stack->token[i].type == OPERATOR_T)
				&& tree_offset > 1)
			handle_non_cmd(stack->token[i], stack_tree, &tree_offset, envp);
		i++;
	}
	i = 1;
	free(stack->token);
	root = stack_tree[0];
	free(stack_tree);
	set_ids(root, &i);
	set_count(root, i);
	return (root);
}
