/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:44:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/17 16:48:36 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    env_command(t_env_vars *env_vars)
{
	while (env_vars)
	{
		if (env_vars->env_val && env_vars->env_name[0] != '?')
			printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
		env_vars = env_vars->next;
	}
}

void    exit_command(char **cmds, t_env_vars **head, int child, t_token_tree *tree)
{
	if (child)
    	write(1, "exit\n", 6);
    ft_close(cmds, head, tree);
    exit(0);
}

int	home_case(t_env_vars *head)
{
	t_env_vars	*home_path;

	home_path = search_for_env_var(&head, "HOME");
	if (home_path)
	{	
		if (chdir(home_path->env_val) != 0)
			return (print_err(strerror(errno), NULL, NULL), exit(1), -1);
	}
	else
	{
		print_err("minishell: cd: HOME not set\n", NULL, NULL);
		return (-1);
	}
	return (0);
}

int	oldpwd_case(t_env_vars *head)
{
	t_env_vars	*oldpwd;

	oldpwd = search_for_env_var(&head, "OLDPWD");
	if (oldpwd && oldpwd->env_val)
	{
		if (chdir(oldpwd->env_val) != 0)
			return (print_err(strerror(errno), NULL, NULL), exit(1), -1);
		printf("%s\n", oldpwd->env_val);
	}
	else
	{
		print_err("minishell: cd: OLDPWD not set\n", NULL, NULL);
		return (-1);
	}
	return (0);
}

int	check_minus_n(char *echo_flag)
{
	if (*echo_flag == '-')
	{
		echo_flag++;
		while (*echo_flag)
		{
			if (*echo_flag != 'n')
				return (-1);
			echo_flag++;
		}
	}
	else if (*echo_flag != '-')
		return (-1);
	return (0);
}
