/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:28:06 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/20 18:25:42 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	add_slash(char **paths_w, char **paths, char **cmds, t_token_tree *tree)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (paths_w[i])
	{
		j = 0;
		paths[i] = malloc(sizeof(char) * (ft_strlen(paths_w[i]) + 2)); //leaks
		if (!paths[i])
			return (free_2d_array(paths), free_2d_array(paths_w),
				ft_close(cmds, tree->head, tree), exit(1));
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

char *find_path(char **paths, char *cmd, char **cmds, t_token_tree *tree)
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
			return (free_2d_array(paths), free(paths), ft_close(cmds, tree->head, tree),
				exit(1), NULL);
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

char	*find_correct_path(char **cmds, t_token_tree *tree)
{
	char	**paths_w;
	char	**paths;
	char	*path;

	paths_w = ft_split(getenv("PATH"), ':'); //leaks
	if (!paths_w)
		return (ft_close(cmds, tree->head, tree), exit(1), NULL);
	paths = malloc(sizeof(char *) * (count_2d_array_elements(paths_w) + 1));
	if (!paths)
		return (free_2d_array(paths_w), ft_close(cmds, tree->head, tree),
			exit(1), NULL);
	paths[count_2d_array_elements(paths_w)] = NULL;
	add_slash(paths_w, paths, cmds, tree);
	path = find_path(paths, cmds[0], cmds, tree);
	if (!path)
		return (free_2d_array(paths), free_2d_array(paths_w), NULL);
	free_2d_array(paths_w);
	free_2d_array(paths);
	return (path);
}

int	execute_rest(char **cmds, t_token_tree *tree)
{
	char		*path;
	t_env_vars	*tmp;
	struct stat	buff;

	path = NULL;
	tmp = search_for_env_var(tree->head, "?");
	if (!ft_strchr(cmds[0], '/'))
		path = find_correct_path(cmds, tree);
	else
	{
		path = ft_strdup(cmds[0]);
		if (!path)
			return (ft_close(cmds, tree->head, tree), -1);
		stat(path, &buff);
		if (S_ISDIR(buff.st_mode))
			return (print_err("minishell: ", path, ": is a directory\n"), -1);
	}
	if (path)
	{
		if (execute_using_execve(tmp, cmds, path, tree->envp) == -1)
			return (-1);
	}
	else
	{
		print_err("minishell: ", cmds[0], ": command not found\n");
		define_exit_status(tmp, "127");
		return (-1);
	}
	return (0);
}

int exec_command(t_token_tree *tree, char **cmds, int child)
{
	t_env_vars	*tmp;

	tmp = search_for_env_var(tree->head, "?");
	if (define_exit_status(tmp, "0") == -1)
		return (free_envs(tree->head), -1);
	if (!ft_strcmp(cmds[0], "cd"))
	{
		if (cd_command(cmds[1], *tree->head) == -1)
			return (handle_builtins_failure(tree, cmds));
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{    
		if (pwd_command() == -1)
			return (handle_builtins_failure(tree, cmds));
	}
	else
		return (builtins_rest(tree, cmds, tree->head, child));
	return (0);
}
