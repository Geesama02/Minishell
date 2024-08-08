/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:44:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/08 14:30:34 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	env_command(t_token_tree *tree, char **cmds, t_env_vars *head)
{
	if (search_for_env(&head, "PATH"))
	{
		while (head)
		{
			update_underscore_env("/usr/bin/env", cmds, *tree->head, tree);
			if (head->env_val && head->env_name[0] != '?'
				&& head->visible == 1)
				printf("%s=%s\n", head->env_name, head->env_val);
			head = head->next;
		}
	}
	else
	{
		print_err("minishell: env: No such file or directory\n", NULL, NULL);
		if (define_exit_status(head, "127") == -1)
			return (ft_close(cmds, tree->head, tree), exit(1));
		update_underscore_env(NULL, cmds, *tree->head, tree);
	}
}

int	exit_command(char **cmds, int child, t_token_tree *tree)
{
	long		exit_s;
	t_env_vars	*tmp;

	if (child)
		write(1, "exit\n", 6);
	tmp = search_for_env(tree->head, "?");
	if (tmp)
		exit_s = ft_atoi_long(tmp->env_val);
	if (g_is_heredoc[1] == 1)
		exit_s = 1;
	if (cmds[1])
	{
		exit_s = ft_atoi_long(cmds[1]);
		if (check_overflow_multiple_arguments(exit_s, cmds) == -1)
			return (-1);
	}
	ft_close(cmds, tree->head, tree);
	exit(exit_s);
	return (0);
}

int	home_case(char **cmds, t_token_tree *tree, t_env_vars *head)
{
	t_env_vars	*home_path;

	update_underscore_env(NULL, cmds, *tree->head, tree);
	home_path = search_for_env(&head, "HOME");
	if (home_path)
	{
		if (chdir(home_path->env_val) != 0)
			return (print_err(strerror(errno), "\n", NULL),
				ft_close(cmds, &head, tree), exit(1), -1);
		update_oldpwd(search_for_env(&head, "PWD")->env_val, cmds, tree);
		update_pwd(cmds, tree, home_path->env_val);
	}
	else
	{
		print_err("minishell: cd: HOME not set\n", NULL, NULL);
		return (-1);
	}
	return (0);
}

int	oldpwd_case(char **cmds, t_token_tree *tree, t_env_vars *head)
{
	t_env_vars	*oldpwd;
	char		*tmp_pwd;

	update_underscore_env(NULL, cmds, *tree->head, tree);
	oldpwd = search_for_env(&head, "OLDPWD");
	tmp_pwd = ft_strdup(search_for_env(&head, "PWD")->env_val);
	if (!tmp_pwd && errno == ENOMEM)
		return (ft_close(cmds, tree->head, tree), exit(1), -1);
	if (oldpwd && oldpwd->env_val)
	{
		if (chdir(oldpwd->env_val) != 0)
			return (print_err(strerror(errno), "\n", NULL),
				ft_close(cmds, &head, tree), exit(1), -1);
		printf("%s\n", oldpwd->env_val);
		update_pwd(cmds, tree, oldpwd->env_val);
		update_oldpwd(tmp_pwd, cmds, tree);
		free(tmp_pwd);
	}
	else
	{
		free(tmp_pwd);
		print_err("minishell: cd: OLDPWD not set\n", NULL, NULL);
		return (-1);
	}
	return (0);
}

int	check_minus_n(char *echo_flag)
{
	int	i;

	i = 1;
	if (!echo_flag)
		return (-1);
	if (echo_flag[i])
	{
		while (echo_flag[i])
		{
			if (echo_flag[i] != 'n')
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	return (0);
}
