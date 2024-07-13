/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:32:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 10:49:20 by maglagal         ###   ########.fr       */
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

int	execute_cmd(t_token_tree *tree, t_env_vars **head, char **cmds)
{
	int	res;

	res = exec_command(cmds, tree->envp, head);
	if (res == -1)
		return (free_cmds(cmds), free(cmds), -1);
	if (res == -2)
		return (free_envs(head), free_cmds(cmds), free(cmds), free_tree(tree->tree_head_address), exit(1), -1);
	return (0);
}

int	execute_tree(t_token_tree *tree, t_env_vars **head)
{
	int		status;
	char	**cmds;

	cmds = NULL;
	if (tree->type == REDIRECTION_I || tree->type == REDIRECTION_O
		|| tree->type == REDIRECTION_A)
		execute_redirection(tree);
	else if (!tree->right && !tree->left)
	{
		cmds = ft_split_qt(tree->token, ' '); //leaks
		if (!cmds && errno == ENOMEM)
			return (free_envs(head), -1);
		if (execute_cmd(tree, head, cmds) == -1)
			return (-1);
	}
	else if (tree->type == OPERATOR_T)
	{
		if (execute_cmds_with_operators(tree, head) == -1)
			return (free_cmds(cmds), free(cmds), -1);
	}
	else if (tree->type == HEREDOC)
		execute_heredoc(tree->left, tree->right);
	wait(&status);
	free_cmds(cmds);
	free(cmds);
	return (0);
}
