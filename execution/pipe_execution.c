/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:21:44 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/10 16:58:53 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	define_exit_status_pipes(t_token_tree *node, int status)
{
	t_env_vars	*tmp;
	char		*exit_status;

	if (node->id == node->cmd_count)
	{
		tmp = search_for_env_var(node->head, "?", 0);
		exit_status = ft_itoa(status);
		define_exit_status(tmp, exit_status);
	}
}

void    close_all_fds(int stdout_fd, int stdin_fd, int fds[2])
{
	close(fds[1]); //fail
	close(fds[0]); //fail
	close(stdout_fd); //fail
	close(stdin_fd); //fail
}

int execute_left_pipe(t_token_tree *left, int fds[2], int stdout_fd, int stdin_fd)
{
	close(fds[0]); //fail
	dup2(fds[1], 1); //fail
	close(fds[1]); //fail
	if (execute_tree(left, left->head) == -1)
		exit(1);
	close(stdin_fd); //fail
	close(stdout_fd); //fail
	exit(0);
}

int	execute_right_pipe(t_token_tree *right, int fds[2], int stdout_fd, int stdin_fd)
{
	t_env_vars	*tmp;

	tmp = NULL;
	close(fds[1]); //fail
	dup2(fds[0], 0); //fail
	close(fds[0]); //fail
	if (right->id == right->cmd_count)
		dup2(stdout_fd, 1); //fail
	if (execute_tree(right, right->head) == -1)
	{
		tmp = search_for_env_var(right->head, "?", 0);
		exit(ft_atoi(tmp->env_val));
	}
	close(stdin_fd); //fail
	close(stdout_fd); //fail
	exit(0);
}

void    execute_pipe(t_token_tree *left, t_token_tree *right)
{
	pid_t	l_pid;
	pid_t	r_pid;
	int		fds[2];
	int		stdout_fd;
	int		stdin_fd;
	int		status;

	stdout_fd = dup(1); //fail
	stdin_fd = dup(0); //fail
	pipe(fds); //fail
	l_pid = fork(); //fail
	if (!l_pid)
		execute_left_pipe(left, fds, stdout_fd, stdin_fd);
	r_pid = fork(); //fail
	if (!r_pid)
		execute_right_pipe(right, fds, stdout_fd, stdin_fd);
	else
	{
		dup2(stdout_fd, 1); //fail
		dup2(stdin_fd, 0); //fail
		close_all_fds(stdout_fd, stdin_fd, fds);
	}
	wait(&status);
	define_exit_status_pipes(right, WEXITSTATUS(status));
}
