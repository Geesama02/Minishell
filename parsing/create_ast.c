/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:47 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/05 17:03:00 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

t_token_tree	*create_node(char *token, t_t_type type,
	char **envp, t_env_vars **head)
{
	t_token_tree	*node;

	node = malloc(sizeof(t_token_tree));
	if (!node)
		return (NULL);
	node->token = token;
	node->type = type;
	node->envp = envp;
	node->head = head;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	print_tree(t_token_tree *root, int level)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	while (i < level)
	{
		printf("------------");
		i++;
	}
	printf("%s -> %s\n", root->token, print_type(root->type));
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}

void	free_tree(t_token_tree *root)
{
	if (!root)
		return ;
	free(root->token);
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
