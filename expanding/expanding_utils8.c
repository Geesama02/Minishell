/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:41:20 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/09 11:23:25 by oait-laa         ###   ########.fr       */
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
	t_env_vars	*env;

	env = search_for_env(head, "_");
    if (!env)
    {
        env = malloc(sizeof(t_env_vars));
        if (!env && errno == ENOMEM)
			return (free_envs(head), exit(1));
        env->env_name = ft_strdup("_");
        if (!env->env_name && errno == ENOMEM)
			return (free(env), free_envs(head), exit(1));
        env->env_val = ft_strdup("minishell");
         if (!env->env_val && errno == ENOMEM)
			return (free(env), free(env->env_name), free_envs(head), exit(1));
        env->next = NULL;
        env->visible = 1;
        ft_lstadd(head, env);
    }
    else if (env && env->env_val)
    {
        free(env->env_val);
        env->env_val = ft_strdup("minishell");
        if (!env->env_val && errno == ENOMEM)
            return (free_n(env), free_envs(head), exit(1));
    }
}

int	var_in_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_inside_quotes(str, i)
			&& inside_single_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	remove_empty(char ***cmds, int n, t_token_tree *tree, char *old)
{
	if ((n >= 0)
		&& (*cmds)[n][0] == '\0' && (has_quotes(old, '\"') && has_quotes(old, '\'')))
	{
		*cmds = remove_from_array(*cmds, n);
		if (!*cmds)
			return (free(old), ft_close(NULL, tree->head, tree), exit(1));
	}
	free(old);
}