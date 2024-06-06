/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:16 by maglagal          #+#    #+#             */
/*   Updated: 2024/06/03 17:49:29 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int cd_command(char *path)
{
	if (!path || (path && !ft_strcmp(path, "~")))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			write(2, "chdir() failed!!\n", 18);
			exit(1);
		}
	}
	else if (chdir(path) != 0)
	{
		write(2, "chdir() failed!!\n", 18);
		exit(1);
	}
	return (0);
}

int pwd_command()
{
	char	buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
	{
		write(2, "getcwd() failed!!\n", 19);
		exit(1);
	}
	else
	{    
		write(1, buff, ft_strlen(buff));
		write(1, "\n", 1);
	}
	return (0);
}

int echo_command(char **cmds, t_env_vars *head)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	if (cmds[i] && !ft_strcmp(cmds[1], "-n"))
	{
		new_line = 0;
		i++;
	}
	if (cmds[i] && ft_strchr(cmds[i], '$'))
		print_env_variable(cmds, head, i);
	else
		print_echo_content(cmds, i, new_line);
	return (0);
}

void	export_command(char **tokens, t_env_vars **head)
{
	int	nbr_envs;

	if (!tokens[1])
		export_without_arguments(*head);
	nbr_envs = count_env_vars(tokens);
	add_env_var(tokens, nbr_envs, head);
}

void	unset_command(t_env_vars **head, char *cmd)
{
	t_env_vars	*tmp;

	tmp = *head;
	if (tmp && !ft_strcmp(tmp->env_name, cmd))
	{    
		tmp->env_name = NULL;
		tmp->env_val = NULL;
		if (tmp->next)
			*head = tmp->next;
		else
			*head = NULL;
		free(tmp);
	}
	else
	{
		while (tmp && tmp->next && ft_strcmp(tmp->next->env_name, cmd))
			tmp = tmp->next;
		if (tmp->next && tmp->next->next)
			replace_nodes_content(tmp->next, tmp->next->next);
		else
		{	
			free(tmp->next);
			tmp->next = NULL;
		}
	}
}

void    env_command(t_env_vars *env_vars)
{
	while (env_vars)
	{
		if (env_vars->env_val)
			printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
		env_vars = env_vars->next;
	}
}

