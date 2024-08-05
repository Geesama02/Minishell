/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:32:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/05 12:57:16 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_expand(t_token_tree *tree, char **str)
{
	if (has_vars(*str))
	{
		*str = split_quotes(*str, tree);
		if (!*str)
			return (ft_close(NULL, tree->head, tree),
				exit(1), -1);
		return (0);
	}
	else
	{
		*str = ignore_quotes(str);
		if (!*str)
			return (ft_close(NULL, tree->head, tree),
				exit(1), -1);
	}
	return (1);
}

int	execute_cmds_with_operators_heredoc(t_token_tree *tree, t_env_vars **head,
		int child)
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
		execute_pipe(tree);
	else if (tree->type == HEREDOC)
		execute_heredoc(tree);
	return (0);
}

int	execute_one_command(t_token_tree *tree, int child)
{
	char	**cmds;
	int		n;
	int	flag = 0;

	n = 0;
	cmds = NULL;
	cmds = ft_split_qt(tree->token, ' ');
	if (!cmds && errno == ENOMEM)
		return (ft_close(NULL, tree->head, tree), exit(1), -1);
	while (cmds[n])
	{
		if (has_quotes(cmds[n], '\'') && has_quotes(cmds[n], '\"'))
			flag = 1;
		check_expand(tree, &cmds[n]);
		if_must_split(&cmds, n, tree, flag);
		flag = 0;
		if (!cmds[n])
			break ;
		n++;
	}
	if (cmds && exec_command(tree, cmds, child) == -1)
		return (free_2d_array(cmds), -1);
	free_2d_array(cmds);
	return (0);
}

int	execute_tree(t_token_tree *tree, t_env_vars **head, int child)
{
	if (tree->type == REDIRECTION_I || tree->type == REDIRECTION_O
		|| tree->type == REDIRECTION_A)
	{
		if (execute_redirection(tree) == -1)
			return (-1);
	}
	else if (!tree->right && !tree->left)
	{
		if (execute_one_command(tree, child) == -1)
			return (-1);
	}
	else if (tree->type == OPERATOR_T || tree->type == HEREDOC)
	{
		if (execute_cmds_with_operators_heredoc(tree, head, child) == -1)
			return (-1);
	}
	wait(NULL);
	return (0);
}
