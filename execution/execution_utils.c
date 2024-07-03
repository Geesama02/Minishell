/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:28:06 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/03 12:15:44 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

char *add_slash(char *string)
{
	int i;
	char *f_string;

	f_string = malloc((sizeof(char) * ft_strlen(string)) + 2); //leaks
	i = 0;
	while (string[i])
	{   
		f_string[i] = string[i];
		i++;
	}
	f_string[i] = '/';
	f_string[i + 1] = '\0';
	return (f_string);
}

char *find_path(char **paths, char *cmd)
{
	int         i;
	char        *path;
	struct stat buffer;

	path = NULL;
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd); //leaks
		if (!stat(path, &buffer))
			return (path);
		else
			i++;
	}
	return (NULL);
}

char	*find_correct_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	paths = ft_split(getenv("PATH"), ':'); //leaks
	while (paths[i])
	{
		paths[i] = add_slash(paths[i]); //leaks
		i++;
	}
	path = find_path(paths, cmd); //leaks
	return (path);
}

int execute_rest(char **cmds, char **envp, t_env_vars **head)
{
	int		status;
	char	*path;
	pid_t	pid;
	t_env_vars	*tmp;

	tmp = *head;
	while(tmp->env_name[0] != '?')
		tmp = tmp->next;
	if (!ft_strchr(cmds[0], '/'))
		path = find_correct_path(cmds[0]);
	else
		path = cmds[0];
	// printf("path = %s\n", path);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, cmds, envp) == -1)
			{
				write(2, "execve() failed!!\n", 19); 
				exit(1);
			}
		}
		wait(&status);
		free(tmp->env_val);
		if (WTERMSIG(status) > 0)
			tmp->env_val = ft_itoa(128 + WTERMSIG(status)); // free later
		else
			tmp->env_val = ft_itoa(WEXITSTATUS(status)); // free later
	}
	else
	{
		write(2, "command not found\n", 18);
		free(tmp->env_val);
		tmp->env_val = ft_strdup("127");
		return (0);
	}
	if (WEXITSTATUS(status) == 1)
		return (-1);
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	return (0);
}

int exec_command(char **cmds, char **envp, t_env_vars **head)
{
	t_env_vars	*tmp;

	tmp = *head;
	while (tmp->env_name[0] != '?')
		tmp = tmp->next;
	free(tmp->env_val);
	tmp->env_val = ft_strdup("0");
	if (!ft_strcmp(cmds[0], "cd"))
	{    
		if (cd_command(cmds[1]) == 1)
		{
			free(tmp->env_val);
			tmp->env_val = ft_strdup("1");
			ft_close(&tmp, cmds, head);
			free(cmds);
			return (-1);
		}
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{    
		if (pwd_command() == 1)
		{
			free(tmp->env_val);
			tmp->env_val = ft_strdup("1");
			ft_close(&tmp, cmds, head);
			free(cmds);
			return (-1);
		}
	}
	else if (!ft_strcmp(cmds[0], "echo"))
		echo_command(cmds, *head);
	else if (!ft_strcmp(cmds[0], "export"))
		export_command(cmds, head);
	else if (!ft_strcmp(cmds[0], "unset"))
		unset_command(head, cmds[1]);
	else if (!ft_strcmp(cmds[0], "env"))
		env_command(*head);
	else if (!ft_strcmp(cmds[0], "exit"))
	{
		ft_close(&tmp, cmds, head);
		free(cmds);
		exit(0);
	}
	else
	{
		if (execute_rest(cmds, envp, head) == -1)
			return (-1);
	}
	return (0);
}
