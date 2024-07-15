/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/15 10:51:09 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	execute_redirection_in(t_token_tree *tree)
{
	int			fd_file;
	int			status;
	pid_t		pid;
	t_env_vars	*tmp;

	null_terminating(tree->right->token, ' ');
	pid = fork(); //fail
	if (!pid)
	{
		
		fd_file = open(tree->right->token, O_RDONLY, S_IRWXU); //fail
		if (fd_file == -1 && errno == ENOENT)
		{
			print_err("minishell: ", tree->right->token, ": No such file or directory\n");
			exit(1);
		}
		dup2(fd_file, 0); //fail
		close(fd_file); //fail
		execute_tree(tree->left, tree->head, pid);
		exit(0);
	}
	wait(&status);
	tmp = search_for_env_var(tree->head, "?", 0);
	define_exit_status(tmp, ft_itoa(WEXITSTATUS(status)));
}

void	execute_redirection_out(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	pid_t	pid;

	null_terminating(tree->right->token, ' ');
	pid = fork(); //fail
	if (pid == -1)
		print_err("fork() failed!!\n", NULL, NULL); //fork() fail
	else if (pid == 0)
	{
		stdout_cp = dup(1);
		fd_file = open(tree->right->token, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU); //fail
		if (fd_file == -1)
		{	
			print_err("open() failed!!\n", NULL, NULL);
			exit(1);
		}
		dup2(fd_file, 1);
		close(fd_file);
		execute_tree(tree->left, tree->head, pid);
		dup2(stdout_cp, 1);
		close(stdout_cp);
		exit(0);
	}
	wait(NULL);
}

void	execute_redirection_append(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	pid_t	pid;

	null_terminating(tree->right->token, ' ');
	pid = fork();
	if (!pid)
	{
		stdout_cp = dup(1);
		fd_file = open(tree->right->token, O_CREAT | O_RDWR | O_APPEND, 00700);
		if (fd_file == -1)
		{
			print_err("open() failed!!\n", NULL, NULL);
			exit(1);
		}
		dup2(fd_file, 1);
		close(fd_file);
		execute_tree(tree->left, tree->head, pid);
		dup2(stdout_cp, 1);
		close(stdout_cp);
		exit(0);
	}
	wait(NULL);
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
