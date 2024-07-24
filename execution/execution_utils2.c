/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/24 11:01:09 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	execute_using_execve(t_token_tree *tree, char **cmds,
	char *path, char **envp)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (handle_fork_failure(tree), -1);
	if (pid == 0)
	{
		if (execve(path, cmds, envp) == -1)
		{
			if (errno == ENOENT)
				exit(127);
			exit(1);
		}
	}
	wait(&status);
	return (exit_execve(status, tree->head, path));
}

int	builtins_rest(t_token_tree *tree, char **cmds, t_env_vars **head, int child)
{
	if (!ft_strcmp(cmds[0], "echo"))
		echo_command(tree, cmds);
	else if (!ft_strcmp(cmds[0], "export"))
	{
		if (export_command(cmds, head, tree) == -1)
			return (handle_builtins_failure(tree, cmds));
	}
	else if (!ft_strcmp(cmds[0], "unset"))
	{
		if (unset_command(cmds, tree) == -1)
			return (handle_builtins_failure(tree, cmds));
	}
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

int	define_exit_status(t_env_vars *head, char *exit_status)
{
	t_env_vars	*tmp;

	tmp = search_for_env_var(&head, "?");
	if (tmp)
	{
		free(tmp->env_val);
		tmp->env_val = ft_strdup(exit_status);
		if (!tmp->env_val && errno == ENOMEM)
			return (-1);
	}
	return (0);
}

int	ft_isalpha_quotes(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 34)
		return (1);
	else
		return (0);
}

char	*file_isdir_case(char **cmds, t_token_tree *tree, char *path)
{
	struct stat	buff;

	path = ft_strdup(cmds[0]);
	if (!path)
		return (ft_close(cmds, tree->head, tree), NULL);
	if (stat(path, &buff) == -1 && errno != ENOENT)
		return (free(path), print_err("stat failed!!\n", NULL, NULL), NULL);
	if (S_ISDIR(buff.st_mode))
		return (print_err("minishell: ", path,
				": is a directory\n"), free(path), NULL);
	return (path);
}
