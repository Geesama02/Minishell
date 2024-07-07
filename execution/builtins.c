/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:16 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/07 17:00:09 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int cd_command(char *path, t_env_vars *head)
{
	struct stat	infos;
	int			res;

	res = stat(path, &infos);
	if (!path)
	{
		if (!search_for_env_var(&head, "HOME", 0))
		{
			ft_printf_err("minishell: cd: HOME not set\n");
			return (-1);
		}
		else
			chdir(search_for_env_var(&head, "HOME", 0)->env_val);
	}
	else if (chdir(path) != 0)
	{
		if (res == -1)
			ft_printf_err("minishell: cd: %s: No such file or directory\n", path);
		else if (S_ISREG(infos.st_mode))
			ft_printf_err("minishell: cd: %s Not a directory\n", path);
		return (-1);
	}
	return (0);
}

int pwd_command()
{
	char	buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
	{
		ft_printf_err("getcwd() failed!!\n");
		return (-1);
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
	(void)head;

	i = 1;
	new_line = 1;
	if (cmds[i] && !ft_strcmp(cmds[1], "-n"))
	{
		new_line = 0;
		i++;
	}
	print_echo_content(cmds, i, new_line);
	return (0);
}

void	export_command(char **tokens, t_env_vars **head)
{
	int	nbr_envs;

	if (!tokens[1])
	{	
		export_without_arguments(*head);
		return ;
	}
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
