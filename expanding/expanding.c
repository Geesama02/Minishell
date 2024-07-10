/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/10 11:17:14 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    export_without_arguments(t_env_vars *p_head)
{
	t_env_vars	*tmp_h;
	t_env_vars	*s_head;

	s_head = display_envs_sorted(p_head);
	tmp_h = s_head;
	while (s_head)
	{
		if (s_head->env_name[0] != '?')
		{
			if (s_head->env_val)
			{
				printf("declare -x %s=\"%s\"\n", s_head->env_name, s_head->env_val);
			}
			else
				printf("declare -x %s\n", s_head->env_name);
		}
		s_head = s_head->next;
	}
	free_envs(&tmp_h);
}

void	lst_add_element(char **tokens, char **cmds, t_env_vars **head,
	int i)
{
	t_env_vars          *new_env;
	t_env_vars          *prev;

	if (*head)
		prev = get_last_node(*head);
	new_env = malloc(sizeof(t_env_vars)); //leaks
	if (!new_env && errno == ENOMEM)
		return (ft_close(tokens, head), free_cmds(cmds), exit(1));
	if (prev)
		prev->next = new_env;
	else if (!prev && i == 1)
		*head = new_env;
	new_env->env_name = ft_strdup(cmds[0]); //leaks
	if (!new_env->env_name && errno == ENOMEM)
		return (ft_close(tokens, head), free_cmds(cmds), exit(1));
	if (ft_strchr(cmds[1], '$'))
		null_terminating(cmds[1]);
	if (cmds[1])
	{
		new_env->env_val = ft_strdup(cmds[1]); //leaks
		if (!new_env->env_val && errno == ENOMEM)
			return (ft_close(tokens, head), free_cmds(cmds), exit(1));
	}
	else
		new_env->env_val = NULL;
	new_env->next = NULL;
}

int	add_or_append(char **cmds, t_env_vars **head,
	char **tokens, int i)
{
	char		*env_name;
	t_env_vars	*tmp;

	tmp = search_for_env_var(head, "?", 0);
	if (ft_strchr(cmds[0], '+'))
	{
		env_name = ft_strtrim(cmds[0], "+"); //leaks
		if (!env_name && errno == ENOMEM)
			return (free_cmds(cmds), ft_close(tokens, head), exit(1), -1);
		if (append_env_var(*head, env_name, cmds[1]) == -1)
			return (-1);
		free(env_name);
	}
	else if (ft_isalpha(cmds[0][0]) && is_string(cmds[0]))
	{
		search_for_env_var(head, cmds[0], 1);
		lst_add_element(tokens, cmds, head, i);
	}
	else
	{
		define_exit_status(tmp, "1");
		ft_printf_err("export: `%s' : not a valid identifier\n", tokens[i]);
	}
	return (0);
}

void	add_env_var(char **tokens, int nbr_envs, t_env_vars **head)
{
	int		i;
	char	**cmds;

	i = 1;
	cmds = NULL;
	while (i <= nbr_envs)
	{
    	cmds = ft_split_one(tokens[i], '=');
		if (!cmds)
			return (ft_close(tokens, head), exit(1));
		if (add_or_append(cmds, head, tokens, i) == -1)
			return ;
		free_cmds(cmds);
		free(cmds);
		i++;
	}
}
