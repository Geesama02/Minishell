/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 12:38:11 by maglagal         ###   ########.fr       */
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

int	builtins_rest(t_token_tree *tree, char **cmds, t_env_vars **head, int child)
{
	if (!ft_strcmp(cmds[0], "echo"))
		echo_command(tree, cmds);
	else if (!ft_strcmp(cmds[0], "export"))
		export_command(cmds, head, tree);
	else if (!ft_strcmp(cmds[0], "unset"))
		unset_command(head, cmds, tree);
	else if (!ft_strcmp(cmds[0], "env"))
		env_command(*head);
	else if (!ft_strcmp(cmds[0], "exit"))
		exit_command(cmds, head, child, tree);
	else
	{
		if (execute_rest(cmds, tree) == -1)
			return (-1);
	}
	return (0);
}

int	define_exit_status(t_env_vars *tmp, char *exit_status)
{
	if (tmp->env_val)
		free(tmp->env_val);
	tmp->env_val = ft_strdup(exit_status);
	if (!tmp->env_val && errno == ENOMEM)
		return (-1);
	return (0);
}

int	ft_isalpha_quotes(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 34)
		return (1);
	else
		return (0);
}
