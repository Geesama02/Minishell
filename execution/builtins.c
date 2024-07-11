/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:16 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/11 18:40:21 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int cd_command(char *path, t_env_vars *head)
{
	if (!path || !ft_strcmp(path, "~"))
	{	
		if (home_case(head) == -1)
			return (-1);
	}
	else if (!ft_strcmp(path, "-"))
	{	
		if (oldpwd_case(head))
			return (-1);
	}
	else
	{
		chdir(path);
		if (errno == ENOENT)
			ft_printf_err("minishell: cd: %s: No such file or directory\n", path);
		else if (errno == ENOTDIR)
			ft_printf_err("minishell: cd: %s Not a directory\n", path);
		else if (errno)
			ft_printf_err("chdir failed!!\n");
		return (-1);
	}
	return (0);
}

int pwd_command()
{
	char	buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
	{
		ft_printf_err("%s\n", strerror(errno));
		return (-1);
	}
	else
	{    
		write(1, buff, ft_strlen(buff));
		write(1, "\n", 1);
	}
	return (0);
}

int echo_command(char **cmds)
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
	if (print_echo_content(cmds, i, new_line) == 0)
		return (0);
	return (1);
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
		if (tmp->next)
			*head = tmp->next;
		else
			*head = NULL;
		free_node(tmp);
	}
	else
	{
		while (tmp && tmp->next && ft_strcmp(tmp->next->env_name, cmd))
			tmp = tmp->next;
		if (tmp->next && tmp->next->next)
			replace_nodes_content(tmp->next, tmp->next->next);
		else if (tmp->next && !tmp->next->next)
		{
			free_node(tmp->next);
			tmp->next = NULL;
		}
	}
}
