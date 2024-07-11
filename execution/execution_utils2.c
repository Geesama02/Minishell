/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/11 18:41:46 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	execute_using_execve(t_env_vars *tmp, char **cmds,
	char *path, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmds, envp) == -1)
		{
			ft_printf_err("%s\n", strerror(errno));
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	wait(&status);
	free(tmp->env_val);
	if (WTERMSIG(status) > 0)
		tmp->env_val = ft_itoa(128 + WTERMSIG(status)); // free later
	else
		tmp->env_val = ft_itoa(WEXITSTATUS(status)); // free later
	if (WEXITSTATUS(status))
		return (-1);
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	return (0);
}

int	builtins_rest(char **cmds, char **envp, t_env_vars **head)
{
	if (!ft_strcmp(cmds[0], "echo"))
	{
		if(echo_command(cmds) == 0)
			return (-2);
	}
	else if (!ft_strcmp(cmds[0], "export"))
		export_command(cmds, head);
	else if (!ft_strcmp(cmds[0], "unset"))
		unset_command(head, cmds[1]);
	else if (!ft_strcmp(cmds[0], "env"))
		env_command(*head);
	else if (!ft_strcmp(cmds[0], "exit"))
		exit_command(cmds, head);
	else
	{
		if (execute_rest(cmds, envp, head) == -1)
			return (-1);
	}
	return (0);
}

int	define_exit_status(t_env_vars *tmp, char *exit_status)
{
	free(tmp->env_val);
	tmp->env_val = ft_strdup(exit_status);
	if (!tmp->env_val && errno == ENOMEM)
		return (-1);
	return (0);
}
