/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 11:36:40 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	execute_redirection_in(t_token_tree *tree)
{
	int			fd_file;
	int			status;
	pid_t		pid;
	t_env_vars	*tmp;

	pid = fork(); //fail
	if (!pid)
	{
		fd_file = open(tree->right->token, O_RDONLY, 00700); //fail
		if (errno == ENOENT)
		{
			print_err("minishell: ", tree->right->token," : No such file or directory\n");
			exit(1);
		}
		dup2(fd_file, 0); //fail
		close(fd_file); //fail
		execute_tree(tree->left, tree->head);
		exit(0);
	}
	wait(&status);
	tmp = search_for_env_var(tree->head, "?", 0);
	define_exit_status(tmp, ft_itoa(WEXITSTATUS(status)));
}

void    execute_redirection_out(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	pid_t	pid;

	pid = fork(); //fail
	if (pid == -1)
		print_err("fork() failed!!\n", NULL, NULL); //fork() fail
	else if (pid == 0)
	{
		stdout_cp = dup(1);
		fd_file = open(tree->right->token, O_CREAT | O_RDWR | O_TRUNC, 00700); //fail
		if (fd_file == -1)
			print_err("open() failed!!\n", NULL, NULL); //open() fail
		dup2(fd_file, 1);
		close(fd_file);
		execute_tree(tree->left, tree->head);
		dup2(stdout_cp, 1);
		close(stdout_cp);
		exit(0);
	}
	wait(NULL);
}

void    execute_redirection(t_token_tree *tree)
{
	if (tree->type == REDIRECTION_O)
		execute_redirection_out(tree);
	else if (tree->type == REDIRECTION_I)
		execute_redirection_in(tree);
}
