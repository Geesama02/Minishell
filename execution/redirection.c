/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/19 12:42:05 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	expand_files(t_token_tree *tree)
{
	char **cmds;
	char *old_filename;

	old_filename = ft_strdup(tree->token);
	if (!old_filename)
		return (print_err("malloc failed!!\n", NULL, NULL), exit(3));
	check_expand(tree);
	if (tree->token[0] == 0)
		return (print_err("minishell: ", old_filename, ": ambiguous redirect\n"
			), exit(1));
	cmds = ft_split(tree->token, ' ');
	if (!cmds)
		return (print_err("malloc failed!!\n", NULL, NULL), exit(3));
	if (count_2d_array_elements(cmds) > 1)
		return (print_err("minishell: ", old_filename, ": ambiguous redirect\n"
			), exit(1));
	printf("token -> %s\n", tree->token);
}

void	execute_redirection_in(t_token_tree *tree)
{
	int			fd_file;
	int			status;
	pid_t		pid;
	t_env_vars	*tmp;

	// null_terminating(tree->right->token, ' ');
	pid = fork(); //fail
	if (!pid)
	{
		expand_files(tree->right);
		fd_file = open(ignore_quotes(&tree->right->token), O_RDONLY, S_IRWXU); //fail
		if (fd_file == -1 && errno == ENOENT)
		{
			print_err("minishell: ", tree->right->token, ": No such file or directory\n");
			exit(1);
		}
		dup2(fd_file, 0); //fail
		close(fd_file); //fail
		if (tree->left->token[0] != '\0')
			execute_tree(tree->left, tree->head, pid);
		exit(0);
	}
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	tmp = search_for_env_var(tree->head, "?");
	define_exit_status(tmp, ft_itoa(WEXITSTATUS(status)));
}

void	execute_redirection_out(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	int		status;
	pid_t	pid;
	t_env_vars *tmp;

	// null_terminating(tree->right->token, ' ');
	pid = fork(); //fail
	if (pid == -1)
		print_err("fork() failed!!\n", NULL, NULL); //fork() fail
	else if (pid == 0)
	{
		expand_files(tree->right);
		stdout_cp = dup(1);
		fd_file = open(ignore_quotes(&tree->right->token), O_CREAT | O_RDWR | O_TRUNC, S_IRWXU); //fail
		if (fd_file == -1)
		{
			print_err("open() failed!!\n", NULL, NULL);
			exit(1);
		}
		dup2(fd_file, 1);
		close(fd_file);
		if (tree->left->token[0] != '\0')
			execute_tree(tree->left, tree->head, pid);
		dup2(stdout_cp, 1);
		close(stdout_cp);
		exit(0);
	}
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	tmp = search_for_env_var(tree->head, "?");
	define_exit_status(tmp, ft_itoa(WEXITSTATUS(status)));
}

void	execute_redirection_append(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	int		status;
	pid_t	pid;
	t_env_vars *tmp;

	// null_terminating(tree->right->token, ' ');
	pid = fork();
	if (!pid)
	{
		expand_files(tree->right);
		stdout_cp = dup(1);
		fd_file = open(ignore_quotes(&tree->right->token), O_CREAT | O_RDWR | O_APPEND, 00700);
		if (fd_file == -1)
		{
			print_err("open() failed!!\n", NULL, NULL);
			exit(1);
		}
		dup2(fd_file, 1);
		close(fd_file);
		if (tree->left->token[0] != 0)
			execute_tree(tree->left, tree->head, pid);
		dup2(stdout_cp, 1);
		close(stdout_cp);
		exit(0);
	}
	wait(&status);
	if (WEXITSTATUS(status) == 3)
		return (ft_close(NULL, tree->head, tree), exit(1));
	tmp = search_for_env_var(tree->head, "?");
	define_exit_status(tmp, ft_itoa(WEXITSTATUS(status)));
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
