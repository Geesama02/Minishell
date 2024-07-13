/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:16 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 09:04:24 by maglagal         ###   ########.fr       */
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
			print_err("minishell: cd: ", path, " : No such file or directory\n");
		else if (errno == ENOTDIR)
			print_err("minishell: cd: ", path, " Not a directory\n");
		else if (errno)
			print_err("chdir failed!!\n", NULL, NULL);
		return (-1);
	}
	return (0);
}

int pwd_command()
{
	char	buff[PATH_MAX];

	if (!getcwd(buff, sizeof(buff)))
	{
		print_err(strerror(errno), NULL, NULL);
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
	if (!ft_isalpha(cmd[0]))
		print_err("minishell: unset: ", cmd, ": is not a valid identifier\n");
	else if (tmp && !ft_strcmp(tmp->env_name, cmd))
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
