/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/09 14:32:35 by oait-laa         ###   ########.fr       */
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
	update_underscore_env(prev->env_name, cmds, *tree->head, tree);
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
			if (s_head->env_val && s_head->visible == 1
				&& ft_strcmp(s_head->env_name, "_"))
			{
				printf("declare -x %s=\"%s\"\n", s_head->env_name,
					s_head->env_val);
			}
			else if (s_head->visible == 1 && ft_strcmp(s_head->env_name, "_"))
				printf("declare -x %s\n", s_head->env_name);
		}
		s_head = s_head->next;
	}
	free_envs(&tmp_h);
}

void	create_newenv(char **tokens, t_token_tree *tree, char **cmds,
	t_env_vars *new_env)
{
	create_name_val_env(cmds, tokens, tree, new_env);
	new_env->next = NULL;
	new_env->visible = 1;
	if (new_env->env_name && new_env->env_name[0] == '\"')
		new_env->env_name = ignore_first_last_quotes(new_env->env_name);
	if (new_env->env_val && new_env->env_val[0] == '\"')
		new_env->env_val = ignore_first_last_quotes(new_env->env_val);
	update_underscore_env(new_env->env_name, cmds, *tree->head, tree);
}

int	add_or_append(char **cmds, t_token_tree *tree,
	char **tokens)
{
	char	*envname;

	envname = ft_strtrim(cmds[0], "+");
	if (!check_plus_op(cmds[0]) && search_for_env(tree->head, envname))
		append_env_var(envname, cmds[1], cmds, tree);
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
	int			cmd_status;

	cmd_status = 0;
	i = 1;
	cmds = NULL;
	while (i <= nbr_envs)
	{
		cmds = ft_split_one(tokens[i], '=');
		if (!cmds && errno == ENOMEM)
			return (ft_close(tokens, head, tree), exit(1), -1);
		if (add_or_append(cmds, tree, tokens) == -1)
		{
			update_underscore_env(NULL, tokens, *tree->head, tree);
			cmd_status = -1;
			define_exit_status(*head, "1");
			print_err("minishell: export: `", tokens[i],
				"': not a valid identifier\n");
		}
		free_2d_array(cmds);
		i++;
	}
	return (cmd_status);
}
