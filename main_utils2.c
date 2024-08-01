/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:34:15 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/01 13:20:48 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse_header.h"

void	handle_shlvl(t_env_vars *head)
{
	t_env_vars	*lastnode;
	t_env_vars	*shlvl;
	int			shlvl_num;

	shlvl = search_for_env_var(&head, "SHLVL");
	if (shlvl)
	{
		shlvl_num = ft_atoi(shlvl->env_val);
		shlvl_num++;
		free(shlvl->env_val);
		shlvl->env_val = ft_itoa(shlvl_num);
	}
	else
	{
		lastnode = get_last_node(head);
		shlvl = malloc(sizeof(t_env_vars));
		lastnode->next = shlvl;
		shlvl->env_name = ft_strdup("SHLVL");
		shlvl->env_val = ft_strdup("1");
		shlvl->visible = 1;
		shlvl->next = NULL;
	}
}

void	check_path_and_create(t_env_vars *head)
{
	t_env_vars	*path;

	path = search_for_env_var(&head, "PATH");
	if (!path)
	{
		path = malloc(sizeof(t_env_vars));
		path->env_name = ft_strdup("PATH");
		path->env_val = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
			);
		path->next = NULL;
		path->visible = 0;
		ft_lstadd(&head, path);
	}
}

void	handle_oldpwd(t_env_vars *head)
{
	t_env_vars	*oldpwd;

	oldpwd = search_for_env_var(&head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->env_val);
		oldpwd->env_val = NULL;
	}
	else
	{
		oldpwd = malloc(sizeof(t_env_vars));
		oldpwd->env_name = ft_strdup("OLDPWD");
		oldpwd->env_val = NULL;
		oldpwd->visible = 1;
		oldpwd->next = NULL;
		ft_lstadd(&head, oldpwd);
	}
}
