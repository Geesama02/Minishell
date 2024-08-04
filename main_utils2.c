/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:34:15 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 15:46:33 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse_header.h"

void	handle_shlvl(t_env_vars **head)
{
	t_env_vars	*shlvl;

	shlvl = search_for_env(head, "SHLVL");
	if (shlvl)
		shlvl_cases(shlvl, head);
	else
	{
		shlvl = malloc(sizeof(t_env_vars));
		if (!shlvl && errno == ENOMEM)
			return (free_envs(head), exit(1));
		shlvl->env_name = ft_strdup("SHLVL");
		if (!shlvl->env_name && errno == ENOMEM)
			return (free(shlvl), free_envs(head), exit(1));
		shlvl->env_val = ft_strdup("1");
		if (!shlvl->env_val && errno == ENOMEM)
			return (free(shlvl), free(shlvl->env_name), free_envs(head),
				exit(1));
		shlvl->visible = 1;
		shlvl->next = NULL;
		ft_lstadd(head, shlvl);
	}
}

void	check_path_and_create(t_env_vars *head)
{
	t_env_vars	*path;

	path = search_for_env(&head, "PATH");
	if (!path)
	{
		path = malloc(sizeof(t_env_vars));
		if (!path)
			return (free(head), exit(1));
		path->env_name = ft_strdup("PATH");
		if (!path->env_name && errno == ENOMEM)
			return (free(path), free_envs(&head), exit(1));
		path->env_val = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
				);
		if (!path->env_val && errno == ENOMEM)
			return (free(path), free(path->env_name), free_envs(&head),
				exit(1));
		path->next = NULL;
		path->visible = 0;
		ft_lstadd(&head, path);
	}
}

void	handle_oldpwd(t_env_vars **head)
{
	t_env_vars	*oldpwd;

	oldpwd = search_for_env(head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->env_val);
		oldpwd->env_val = NULL;
	}
	else
	{
		oldpwd = malloc(sizeof(t_env_vars));
		if (!oldpwd)
			return (free_envs(head), exit(1));
		oldpwd->env_name = ft_strdup("OLDPWD");
		if (!oldpwd->env_name)
			return (free(oldpwd), free_envs(head), exit(1));
		oldpwd->env_val = NULL;
		oldpwd->visible = 1;
		oldpwd->next = NULL;
		ft_lstadd(head, oldpwd);
	}
}

void	update_pwd(char **cmds, t_token_tree *tree, char *to_set)
{
	t_env_vars	*pwd;

	pwd = search_for_env(tree->head, "PWD");
	if (pwd)
	{
		free(pwd->env_val);
		pwd->env_val = ft_strdup(to_set);
		if (!pwd->env_val && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), exit(1));
	}
	else
	{
		pwd = malloc(sizeof(t_env_vars));
		if (!pwd && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), exit(1));
		pwd->env_name = ft_strdup("PWD");
		if (!pwd->env_name && errno == ENOMEM)
			return (free(pwd), ft_close(cmds, tree->head, tree), exit(1));
		pwd->env_val = ft_strdup(to_set);
		if (!pwd->env_val && errno == ENOMEM)
			return (free_n(pwd), ft_close(cmds, tree->head, tree), exit(1));
		pwd->visible = 0;
		pwd->next = NULL;
		ft_lstadd(tree->head, pwd);
	}
}

void	handle_pwd(t_env_vars **head)
{
	char		buffer[PATH_MAX];
	t_env_vars	*pwd;

	pwd = search_for_env(head, "PWD");
	if (!pwd)
	{
		pwd = malloc(sizeof(t_env_vars));
		if (!pwd && errno == ENOMEM)
			return (free_envs(head), exit(1));
		pwd->env_name = ft_strdup("PWD");
		if (!pwd->env_name && errno == ENOMEM)
			return (free(pwd), free_envs(head), exit(1));
		getcwd(buffer, sizeof(buffer));
		pwd->env_val = ft_strdup(buffer);
		if (!pwd->env_val && errno == ENOMEM)
			return (free(pwd), free(pwd->env_name), free_envs(head), exit(1));
		pwd->next = NULL;
		pwd->visible = 1;
		ft_lstadd(head, pwd);
	}
}
