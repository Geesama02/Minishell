/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:41:20 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/07 12:02:26 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    create_name_val_env(char **cmds, char **tokens,
    t_token_tree *tree, t_env_vars *new_env)
{
    char	*envname;

	envname = ft_strtrim(cmds[0], "+");
	new_env->env_name = ft_strdup(envname);
	if (!new_env->env_name && errno == ENOMEM)
		return (free(envname), ft_close(tokens, tree->head, NULL),
			free_2d_array(cmds), exit(1));
	free(envname);
	if (ft_strchr(cmds[1], '$'))
		null_terminating(cmds[1], '$');
	if (cmds[1])
	{
		new_env->env_val = ft_strdup(cmds[1]);
		if (!new_env->env_val && errno == ENOMEM)
			return (ft_close(tokens, tree->head, NULL),
				free_2d_array(cmds), exit(1));
	}
	else
		new_env->env_val = NULL;
}

void    handle_underscore(t_env_vars **head)
{
	t_env_vars	*underscore_env;

	underscore_env = search_for_env(head, "_");
    if (!underscore_env)
    {
        underscore_env = malloc(sizeof(t_env_vars));
        if (!underscore_env && errno == ENOMEM)
			return (free_envs(head), exit(1));
        underscore_env->env_name = ft_strdup("_");
        if (!underscore_env->env_name && errno == ENOMEM)
			return (free(underscore_env), free_envs(head), exit(1));
        underscore_env->env_val = ft_strdup("minishell");
         if (!underscore_env->env_val && errno == ENOMEM)
			return (free(underscore_env), free(underscore_env->env_name),
                free_envs(head), exit(1));
        underscore_env->next = NULL;
        underscore_env->visible = 1;
        ft_lstadd(head, underscore_env);
    }
    else if (underscore_env && underscore_env->env_val)
    {
        free(underscore_env->env_val);
        underscore_env->env_val = ft_strdup("minishell");
    }
}
