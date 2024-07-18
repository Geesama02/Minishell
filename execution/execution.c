/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:32:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/18 17:07:54 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_expand(t_token_tree *tree)
{
	if (has_vars(tree->token))
	{
		tree->token = expand_vars(tree->token, *tree->head);
		if (!tree->token)
			return (ft_close(NULL, tree->head, tree),
				exit(1), -1);
		return (0);
	}
	return (1);
}

int execute_cmds_with_operators(t_token_tree *tree, t_env_vars **head, int child)
{
	if (!ft_strcmp(tree->token, "&&"))
	{
		if (!execute_tree(tree->left, head, child))
			execute_tree(tree->right, head, child);
		else
			return (-1);
	}
	else if (!ft_strcmp(tree->token, "||"))
	{
		if (execute_tree(tree->left, head, child) == -1)
		{
			if (execute_tree(tree->right, head, child) == -1)
				return (-1);
		}
	}
	else if (!ft_strcmp(tree->token, "|"))
		execute_pipe(tree->left, tree->right);
	return (0);
}

int	execute_tree(t_token_tree *tree, t_env_vars **head, int child)
{
	int		status;
	char	**cmds;

	cmds = NULL;
	if (tree->type == REDIRECTION_I || tree->type == REDIRECTION_O
		|| tree->type == REDIRECTION_A)
		execute_redirection(tree);
	else if (!tree->right && !tree->left)
	{
		check_expand(tree);
		cmds = ft_split_qt(tree->token, ' '); //leaks
		if (!cmds && errno == ENOMEM)
			return (free_envs(head), free_tree(tree), exit(1), -1);
		cmds = ignore_quotes_2d_array(cmds);
		if (cmds && exec_command(tree, cmds, head, child) == -1)
			return (free_2d_array(cmds), -1);
	}
	else if (tree->type == OPERATOR_T)
	{
		if (execute_cmds_with_operators(tree, head, child) == -1)
			return (free_2d_array(cmds) -1);
	}
	else if (tree->type == HEREDOC)
		execute_heredoc(tree->left, tree->right);
	wait(&status);
	free_2d_array(cmds);
	return (0);
}
