/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:21:44 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/20 17:19:12 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	define_exit_status_pipes(t_token_tree *node, int status)
{
	t_env_vars	*tmp;
	char		*exit_status;

	if (node->id == node->cmd_count)
	{
		tmp = search_for_env_var(node->head, "?");
		exit_status = ft_itoa(status);
		define_exit_status(tmp, exit_status);
	}
}

void    reset_and_close_all_fds(int stdout_fd, int stdin_fd, int fds[2], t_token_tree *node)
{
	dup2(stdout_fd, 1); //fail
	dup2(stdin_fd, 0); //fail
	safe_close(fds[1], node); //fail
	safe_close(fds[0], node); //fail
	safe_close(stdout_fd, node); //fail
	safe_close(stdin_fd, node); //fail
}

int execute_left_pipe(t_token_tree *left, int fds[2], int stdout_fd, int stdin_fd)
{
	safe_close(fds[0], left); //fail
	dup2(fds[1], 1); //fail
	safe_close(fds[1], left); //fail
	if (execute_tree(left, left->head, 0) == -1)
	{
		ft_close(NULL, left->head, left);
		exit(1);
	}
	safe_close(stdin_fd, left); //fail
	safe_close(stdout_fd, left); //fail
	ft_close(NULL, left->head, left);
	exit(0);
}

int	execute_right_pipe(t_token_tree *right, int fds[2], int stdout_fd, int stdin_fd)
{
	int			exit_s;
	t_env_vars	*tmp;

	tmp = NULL;
	safe_close(fds[1], right); //fail
	dup2(fds[0], 0); //fail
	safe_close(fds[0], right); //fail
	if (right->id == right->cmd_count)
		dup2(stdout_fd, 1); //fail
	if (execute_tree(right, right->head, 0) == -1)
	{
		tmp = search_for_env_var(right->head, "?");
		exit_s = ft_atoi(tmp->env_val);
		ft_close(NULL, right->head, right);
		exit(exit_s);
	}
	safe_close(stdin_fd, right); //fail
	safe_close(stdout_fd, right); //fail
	ft_close(NULL, right->head, right);
	exit(0);
}

void    execute_pipe(t_token_tree *left, t_token_tree *right)
{
	pid_t			l_pid;
	pid_t			r_pid;
	int				fds[2];
	int				stdout_fd;
	int				stdin_fd;
	int				status;

	stdout_fd = dup(1); //fail
	stdin_fd = dup(0); //fail
	pipe(fds); //fail
	l_pid = fork(); //fail
	if (l_pid == -1)
		return (print_err("fork failed!!\n", NULL, NULL),
			ft_close(NULL, left->head, left->tree_head_address), exit(1));
	if (!l_pid)
		execute_left_pipe(left, fds, stdout_fd, stdin_fd);
	r_pid = fork(); //fail
	if (r_pid == -1)
		return (print_err("fork failed!!\n", NULL, NULL),
			ft_close(NULL, right->head, right->tree_head_address), exit(1));
	if (!r_pid)
		execute_right_pipe(right, fds, stdout_fd, stdin_fd);
	else
		reset_and_close_all_fds(stdout_fd, stdin_fd, fds, left);
	wait(&status);
	define_exit_status_pipes(right, WEXITSTATUS(status));
}
