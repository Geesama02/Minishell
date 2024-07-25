/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:21:44 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/25 10:04:12 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	define_exit_status_pipes(t_token_tree *node, int status)
{
	char		*exit_status;

	if (node->id == node->cmd_count)
	{
		exit_status = ft_itoa(status);
		define_exit_status(*node->head, exit_status);
		free(exit_status);
	}
}

void	reset_and_close_all_fds(int stdout_fd, int stdin_fd,
		int fds[2], t_token_tree *node)
{
	safe_dup2(node, stdout_fd, 1);
	safe_dup2(node, stdin_fd, 0);
	safe_close(fds[1], node);
	safe_close(fds[0], node);
	safe_close(stdout_fd, node);
	safe_close(stdin_fd, node);
}

int	execute_left_pipe(t_token_tree *left, int fds[2],
		int stdout_fd, int stdin_fd)
{
	safe_close(fds[0], left);
	safe_dup2(left, fds[1], 1);
	safe_close(fds[1], left);
	if (execute_tree(left, left->head, 0) == -1)
	{
		ft_close(NULL, left->head, left);
		safe_close(stdin_fd, left);
		safe_close(stdout_fd, left);
		exit(1);
	}
	safe_close(stdin_fd, left);
	safe_close(stdout_fd, left);
	ft_close(NULL, left->head, left);
	exit(0);
}

int	execute_right_pipe(t_token_tree *right, int fds[2],
		int stdout_fd, int stdin_fd)
{
	int			exit_s;
	t_env_vars	*tmp;

	tmp = NULL;
	safe_close(fds[1], right);
	safe_dup2(right, fds[0], 0);
	safe_close(fds[0], right);
	if (right->id == right->cmd_count)
		safe_dup2(right, stdout_fd, 1);
	if (execute_tree(right, right->head, 0) == -1)
	{
		tmp = search_for_env_var(right->head, "?");
		exit_s = ft_atoi(tmp->env_val);
		ft_close(NULL, right->head, right);
		safe_close(stdin_fd, right);
		safe_close(stdout_fd, right);
		exit(exit_s);
	}
	safe_close(stdin_fd, right);
	safe_close(stdout_fd, right);
	ft_close(NULL, right->head, right);
	exit(0);
}

void	execute_pipe(t_token_tree *tree)
{
	pid_t			c_pid;
	int				fds[2];
	int				stdout_fd;
	int				stdin_fd;
	int				status;

	stdout_fd = safe_dup(1, tree);
	stdin_fd = safe_dup(0, tree);
	if (pipe(fds) == -1)
		return (print_err("pipe() failed!!\n", NULL, NULL),
			ft_close(NULL, tree->head, tree));
	c_pid = fork();
	if (c_pid == -1)
		return (handle_fork_failure(tree));
	if (!c_pid)
		execute_left_pipe(tree->left, fds, stdout_fd, stdin_fd);
	c_pid = fork();
	if (c_pid == -1)
		return (handle_fork_failure(tree));
	if (!c_pid)
		execute_right_pipe(tree->right, fds, stdout_fd, stdin_fd);
	else
		reset_and_close_all_fds(stdout_fd, stdin_fd, fds, tree);
	wait(&status);
	define_exit_status_pipes(tree, WEXITSTATUS(status));
}
