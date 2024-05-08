/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:47 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/08 11:01:03 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

t_token_tree *create_node(char *token, t_t_type type)
{
	t_token_tree *node;

	node = malloc(sizeof(t_token_tree));
	if (!node)
		return (NULL);
	node->token = token;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// t_token_tree *fill_ast(t_token_tree **root, t_token_list *tokens)
// {
// 	int i = 0;

// 	if (!*root)
// 	{
// 		*root = create_node(tokens, tokens->type);
// 	}
// 	t_token_tree *node = *root;
// 	while (tokens[i].token)
// 	{
// 		if (tokens[i].type == AND_OPERATOR || tokens[i].type == OR_OPERATOR)
// 		{
// 			node->left = create_node(tokens - 1, tokens[i - 1].type);
// 			node->right = create_node(tokens + 1, tokens[i + 1].type);

// 			node = node->right;
// 			i++;
// 		}
// 		// else if (tokens[i]->type == PIPE)
// 		// {
// 		// 	node->left = create_node(tokens[i]->token, tokens[i]->type);
// 		// 	node = node->left;
// 		// }
// 		// else if (tokens[i]->type == INPUT_REDIRECTION || tokens[i]->type == OUTPUT_REDIRECTION || tokens[i]->type == APPEND_REDIRECTION)
// 		// {
// 		// 	node->right = create_node(tokens[i]->token, tokens[i]->type);
// 		// 	node = node->right;
// 		// 	node->right = create_node(tokens[i + 1]->token, tokens[i + 1]->type);
// 		// 	node = node->right;
// 		// }
// 		// else
// 		// {
// 		// 	node->left = create_node(tokens[i]->token, tokens[i]->type);
// 		// 	node = node->left;
// 		// }
// 		i++;
// 	}
// 	return (*root);
// }



void print_tree(t_token_tree *root, int level)
{
	if (!root)
		return ;
	int i = 0;
	while (i < level)
	{
		printf("------------");
		i++;
	}
	printf("%s\n", root->token);
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}