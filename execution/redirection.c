/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 10:19:27 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	expand_filenames(t_token_tree *tree)
{
	char	*old_filename;
	char	**cmds;

	old_filename = ft_strdup(tree->token);
	if (!old_filename)
		return (print_err("malloc failed!!\n", NULL, NULL), ft_close(NULL,
			tree->head, tree), free(old_filename), exit(3));
	check_expand(tree);
	if (tree->token[0] == 0)
		return (print_err("minishell: ", old_filename, ": ambiguous redirect\n"
			), free(old_filename), ft_close(NULL, tree->head, tree), exit(1));
	free(old_filename);
	if (has_quotes(tree->token, '\'') && has_quotes(tree->token, '\"'))
	{
		cmds = ft_split(tree->token, ' ');
		if (!cmds)
			return (print_err("malloc failed!!\n", NULL, NULL), ft_close(NULL,
				tree->head, tree), exit(3));
		if (count_2d_array_elements(cmds) > 1)
			return (print_err("minishell: ", old_filename, ": ambiguous redirect\n"
				), free_2d_array(cmds), exit(1));
		free_2d_array(cmds);
	}
}

void	execute_redirection_in(t_token_tree *tree)
{
	int			status;
	pid_t		pid;
	char		*exit_s;

	// null_terminating_rev(tree->right->token);
	pid = fork();
	if (pid == -1)
		return (print_err("fork() failed!!\n", NULL, NULL));
	if (!pid)
		execute_redirec_in(tree, pid);
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	exit_s = ft_itoa(WEXITSTATUS(status));
	define_exit_status(search_for_env_var(tree->head, "?"), exit_s);
	free(exit_s);
}

void	execute_redirection_out(t_token_tree *tree)
{
	int		status;
	pid_t	pid;
	char	*exit_s;

	// null_terminating_rev(tree->right->token);
	pid = fork();
	if (pid == -1)
		return (print_err("fork() failed!!\n", NULL, NULL));
	else if (pid == 0)
		execute_redirec_out(tree, pid);
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	exit_s = ft_itoa(WEXITSTATUS(status));
	define_exit_status(search_for_env_var(tree->head, "?"), exit_s);
	free(exit_s);
}

void	execute_redirection_append(t_token_tree *tree)
{
	int		status;
	pid_t	pid;
	char	*exit_s;

	// null_terminating_rev(tree->right->token);
	pid = fork();
	if (!pid)
		execute_redirec_append(tree, pid);
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	exit_s = ft_itoa(WEXITSTATUS(status));
	define_exit_status(search_for_env_var(tree->head, "?"), exit_s);
	free(exit_s);
}

void	execute_redirection(t_token_tree *tree)
{
	if (tree->type == REDIRECTION_O)
		execute_redirection_out(tree);
	else if (tree->type == REDIRECTION_I)
		execute_redirection_in(tree);
	else if (tree->type == REDIRECTION_A)
		execute_redirection_append(tree);
}
