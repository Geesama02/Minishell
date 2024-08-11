/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:50:48 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 10:32:32 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	execute_or(t_token_tree *tree, t_env_vars **head,
	char **cmds, int child)
{
	if (execute_tree(tree->left, head, child) == -1)
	{
		if (execute_tree(tree->right, head, child) == -1)
			return (update_underscore_env(tree->right->token, cmds,
					*tree->head, tree), -1);
		return (update_underscore_env(tree->right->token, cmds,
				*tree->head, tree), 0);
	}
	return (update_underscore_env(tree->left->token, cmds,
			*tree->head, tree), 0);
}

int	execute_and(t_token_tree *tree, t_env_vars **head,
		char **cmds, int child)
{
	if (!execute_tree(tree->left, head, child))
	{
		if (execute_tree(tree->right, head, child) == -1)
			return (update_underscore_env(tree->right->token, cmds,
					*tree->head, tree), -1);
	}
	else
		return (update_underscore_env(tree->left->token, cmds, *tree->head,
				tree), -1);
	return (update_underscore_env(tree->right->token, cmds, *tree->head,
			tree), 0);
}

char	*remove_space_first_last(char *str)
{
	int		i;
	int		len;
	char	*alloc_str;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			len++;
		i++;
	}
	alloc_str = malloc(sizeof(char) * (len + 1));
	if (!alloc_str)
		return (NULL);
	alloc_newstr_re(str, alloc_str);
	return (free(str), alloc_str);
}

int	count_cmd_redirections(t_token_tree *node)
{
	int	redi;

	redi = 0;
	while (node)
	{
		if (node->type == REDIRECTION_A
			|| node->type == REDIRECTION_I || node->type == REDIRECTION_O)
			redi++;
		else
			return (redi);
		node = node->left;
	}
	return (redi);
}

int	handle_redirection(t_token_tree *tree, char **cmds)
{
	if (count_cmd_redirections(tree) == 2
		&& (tree->left->type == REDIRECTION_O || tree->left->type == REDIRECTION_A)
		&& tree->type == REDIRECTION_I)
	{
		if (execute_redirection(tree->left, cmds) == -1)
			return (-1);
		if (execute_redirection(tree, cmds) == -1)
			return (-1);
	}
	else if ((count_cmd_redirections(tree) == 2)
		&& (tree->left->type == REDIRECTION_I)
		&& (tree->type == REDIRECTION_O || tree->type == REDIRECTION_A))
	{
		if (redirec_edge_case(tree, cmds) == -1)
			return (-1);
	}
	else if (execute_redirection(tree, cmds) == -1)
		return (-1);
	return (0);
}