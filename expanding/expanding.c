/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/29 09:44:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	check_existing(t_env_vars *prev, char **cmds, char **tokens,
	t_token_tree *tree)
{
	free(prev->env_val);
	prev->env_val = ft_strdup(cmds[1]);
	if (!prev->env_val && errno == ENOMEM)
		return (free_2d_array(cmds), ft_close(tokens, tree->head, tree),
			exit(1));
}

void	export_without_arguments(t_env_vars *p_head, char **tokens,
		t_token_tree *tree)
{
	t_env_vars	*tmp_h;
	t_env_vars	*s_head;

	s_head = display_envs_sorted(p_head, tokens, tree);
	tmp_h = s_head;
	while (s_head)
	{
		if (s_head->env_name[0] != '?')
		{
			if (s_head->env_val)
				printf("declare -x %s=\"%s\"\n", s_head->env_name,
					s_head->env_val);
			else
				printf("declare -x %s\n", s_head->env_name);
		}
		s_head = s_head->next;
	}
	free_envs(&tmp_h);
}

void	create_newenv(char **tokens, t_env_vars **head, char **cmds,
	t_env_vars *new_env)
{
	char	*envname;

	envname = ft_strtrim(cmds[0], "+");
	new_env->env_name = ft_strdup(envname);
	free(envname);
	if (!new_env->env_name && errno == ENOMEM)
		return (ft_close(tokens, head, NULL), free_2d_array(cmds), exit(1));
	if (ft_strchr(cmds[1], '$'))
		null_terminating(cmds[1], '$');
	if (cmds[1])
	{
		new_env->env_val = ft_strdup(cmds[1]);
		if (!new_env->env_val && errno == ENOMEM)
			return (ft_close(tokens, head, NULL), free_2d_array(cmds), exit(1));
	}
	else
		new_env->env_val = NULL;
	new_env->next = NULL;
	ignore_quotes(&new_env->env_name);
	ignore_quotes(&new_env->env_val);
}

int	add_or_append(char **cmds, t_token_tree *tree,
	char **tokens)
{
	char *envname;

	envname = ft_strtrim(cmds[0], "+");
	if (!check_plus_op(cmds[0]) && search_for_env_var(tree->head, envname))
		append_element_to_envs(tree, cmds, tokens);
	else if (ft_isalpha_quotes(cmds[0][0]) && is_string(cmds[0]))
		add_element_to_envs(tree, cmds, tokens);
	else
	{
		free(envname);
		return (-1);
	}
	free(envname);
	return (0);
}

int	add_env_var(char **tokens, int nbr_envs, t_env_vars **head,
		t_token_tree *tree)
{
	int			i;
	char		**cmds;

	i = 1;
	cmds = NULL;
	while (i <= nbr_envs)
	{
		cmds = ft_split_one(tokens[i], '=');
		if (!cmds && errno == ENOMEM)
			return (ft_close(tokens, head, tree), exit(1), -1);
		if (add_or_append(cmds, tree, tokens) == -1)
		{
			define_exit_status(*head, "1");
			return (print_err("export: `", tokens[i],
					"': not a valid identifier\n"), free_2d_array(cmds), -1);
		}
		free_2d_array(cmds);
		i++;
	}
	return (0);
}
