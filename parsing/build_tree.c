/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:11:02 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/20 15:22:24 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	set_ids(t_token_tree *root, int *id)
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

void	set_count(t_token_tree *root, int count)
{
	if (!root)
		return ;
	root->cmd_count = count - 1;
	set_count(root->left, count);
	set_count(root->right, count);
}

int	handle_non_cmd(t_token_array token, t_token_tree **stack_tree,
	int *tree_offset, t_tree_vars vars, int *childs)
{
	t_token_tree	*tmp_right;
	t_token_tree	*tmp_left;

	tmp_right = stack_tree[*tree_offset - 1];
	tmp_left = stack_tree[*tree_offset - 2];
	*tree_offset -= 2;
	stack_tree[*tree_offset] = create_node(token.token,
			token.type, vars.envp, vars.head, childs);
	if (!stack_tree[*tree_offset])
		return (0);
	stack_tree[*tree_offset]->right = tmp_right;
	stack_tree[*tree_offset]->left = tmp_left;
	(*tree_offset)++;
	return (1);
}

int	make_nodes(t_stack *stack, int i, t_token_tree **stack_tree,
	t_tree_vars tree_vars, int *childs)
{
	int	tree_offset;

	tree_offset = 0;
	while (stack->token[i].token)
	{
		if (stack->token[i].type == CMD_T
			|| stack->token[i].type == HEREDOC_TOKEN)
		{
			stack_tree[tree_offset] = create_node(stack->token[i].token,
					stack->token[i].type, tree_vars.envp, tree_vars.head, childs);
			if (!stack_tree[tree_offset])
				return (handle_node_failure(stack, stack_tree, tree_offset), 0);
			tree_offset++;
		}
		else if (tree_offset > 1)
		{
			if (!handle_non_cmd(stack->token[i], stack_tree,
					&tree_offset, tree_vars, childs))
				return (handle_node_failure(stack, stack_tree, tree_offset), 0);
		}
		i++;
	}
	return (1);
}
void	set_address(t_token_tree *root, t_token_tree **address)
{
	if (!root)
		return ;
	root->tree_head_address = *address;
	set_address(root->left, address);
	set_address(root->right, address);
}

t_token_tree	*build_tree(t_stack *stack, char **envp,
		t_env_vars **head, int *childs)
{
	int				i;
	t_token_tree	**stack_tree;
	t_token_tree	*root;
	t_tree_vars		tree_vars;

	stack_tree = malloc(sizeof(t_token_tree *) * stack->head);
	if (!stack_tree)
		return (handle_node_failure(stack, stack_tree, -1), exit(1), NULL);
	i = 0;
	tree_vars.envp = envp;
	tree_vars.head = head;
	if (!make_nodes(stack, i, stack_tree, tree_vars, childs))
		return (exit(1), NULL);
	i = 1;
	free(stack->token);
	root = stack_tree[0];
	// printf("stack -> %s\n", stack_tree[1]->token);
	// printf("stack -> %s\n", stack_tree[2]->token);
	free(stack_tree);
	set_ids(root, &i);
	set_count(root, i);
	set_address(root, &root);
	return (root);
}
