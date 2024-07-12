/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:28:06 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/12 17:13:50 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	add_slash(char **paths_w, char **paths)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (paths_w[i])
	{
		j = 0;
		paths[i] = malloc(sizeof(char) * (ft_strlen(paths_w[i]) + 2));
		while (paths_w[i][j])
		{
			paths[i][j] = paths_w[i][j];
			j++;
		}
		paths[i][j] = '/';
		paths[i][j + 1] = '\0';
		i++;
	}
}

char *find_path(char **paths, char *cmd)
{
	int			i;
	char		*path;
	struct stat	buffer;

	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd); //leaks
		if (!path)
			return (free_cmds(paths), NULL);
		if (!stat(path, &buffer))
			return (path);
		else
		{
			free(path);
			i++;
		}
	}
	return (NULL);
}

char	*find_correct_path(char **cmds, t_env_vars **head)
{
	char	**paths_w;
	char	**paths;
	char	*path;

	paths_w = ft_split(getenv("PATH"), ':'); //leaks
	if (!paths_w)
		return (ft_close(cmds, head), exit(1), NULL);
	paths = malloc(sizeof(char *) * (count_2d_array_elements(paths_w) + 1));
	if (!paths)
		return (free_cmds(paths_w), ft_close(cmds, head),
			exit(1), NULL);
	paths[count_2d_array_elements(paths_w)] = NULL;
	add_slash(paths_w, paths);
	path = find_path(paths, cmds[0]);
	if (!path)
		return (free_cmds(paths), free_cmds(paths_w),
			free(paths), free(paths_w), NULL);
	free_cmds(paths_w);
	free_cmds(paths);
	free(paths_w);
	free(paths);
	return (path);
}

int execute_rest(char **cmds, char **envp, t_env_vars **head)
{
	char		*path;
	t_env_vars	*tmp;

	tmp = search_for_env_var(head, "?", 0);
	if (!ft_strchr(cmds[0], '/'))
		path = find_correct_path(cmds, head);
	else
		path = cmds[0];
	if (path)
	{	
		if (execute_using_execve(tmp, cmds, path, envp) == -1)
			return (-1);
	}
	else
	{
		ft_printf_err("minishell: %s: command not found\n", cmds[0]);
		if (define_exit_status(tmp, "127") == -1)
			return (-1);
	}
	free(path);
	return (0);
}

int exec_command(char **cmds, char **envp, t_env_vars **head)
{
	t_env_vars	*tmp;

	tmp = search_for_env_var(head, "?", 0);
	if (define_exit_status(tmp, "0") == -1)
		return (free_envs(head), -1);
	if (!ft_strcmp(cmds[0], "cd"))
	{    
		if (cd_command(cmds[1], *head) == -1)
		{	
			handle_builtins_failure(head, tmp);
			return (-1);
		}
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{    
		if (pwd_command() == -1)
		{
			handle_builtins_failure(head, tmp);
			return (-1);
		}
	}
	else
		return (builtins_rest(cmds, envp, head));
	return (0);
}
