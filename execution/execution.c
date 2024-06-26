/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:32:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/30 11:59:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int execute_cmds_with_operators(t_token_tree *tree, t_env_vars **head)
{
	if (!ft_strcmp(tree->token, "&&"))
	{
		if (!execute_tree(tree->left, head))
			execute_tree(tree->right, head);
		else
			return (-1);
	}
	else if (!ft_strcmp(tree->token, "||"))
	{
		if (execute_tree(tree->left, head) == -1)
		{
			if (execute_tree(tree->right, head) == -1)
				return (-1);
		}
	}
	else if (!ft_strcmp(tree->token, "|"))
		execute_pipe(tree->left, tree->right);
	return (0);
}

int    execute_tree(t_token_tree *tree, t_env_vars **head)
{
	static int	status;
	char		**cmds;

	if (tree->type == REDIRECTION_I || tree->type == REDIRECTION_O)
		execute_redirection(tree);
	else if (!tree->right && !tree->left)
	{
		cmds = ft_split(tree->token, ' ');
		if (exec_command(cmds, tree->envp, head) == -1)
			return (-1);
	}
	else if (tree->type == OPERATOR_T)
	{
		if (execute_cmds_with_operators(tree, head) == -1)
			return (-1);
	}
	else if (tree->type == HEREDOC)
		execute_heredoc(tree->left, tree->right);
	wait(&status);
	return (0);
}
