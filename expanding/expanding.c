/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 10:33:47 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	check_exesting(t_env_vars *prev, char **cmds, char **tokens,
	t_token_tree *tree)
{
	free(prev->env_val);
	prev->env_val = ft_strdup(cmds[1]);
	if (!prev->env_val && errno == ENOMEM)
		return (free_2d_array(cmds), ft_close(tokens, tree->head, tree),
			exit(1));
}

void	export_without_arguments(t_env_vars *p_head, char **tokens, t_token_tree *tree)
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
				printf("declare -x %s=\"%s\"\n", s_head->env_name, s_head->env_val);
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
	new_env->env_name = ft_strdup(cmds[0]);
	if (!new_env->env_name && errno == ENOMEM)
		return (ft_close(tokens, head, NULL), free_2d_array(cmds), exit(1));
	if (ft_strchr(cmds[1], '$'))
		null_terminating(cmds[1], '$');
	if (cmds[1])
	{
		new_env->env_val = ft_strdup(cmds[1]); //leaks
		if (!new_env->env_val && errno == ENOMEM)
			return (ft_close(tokens, head, NULL), free_2d_array(cmds), exit(1));
	}
	else
		new_env->env_val = NULL;
	new_env->next = NULL;
	ignore_quotes(&new_env->env_name);
	ignore_quotes(&new_env->env_val);
}

void	lst_add_element(char **tokens, char **cmds, t_token_tree *tree,
	int i)
{
	t_env_vars	*new_env;
	t_env_vars	*prev;

	if (*tree->head)
		prev = get_last_node(*tree->head);
	new_env = malloc(sizeof(t_env_vars)); //leaks
	if (!new_env && errno == ENOMEM)
		return (ft_close(tokens, tree->head, tree), free_2d_array(cmds), exit(1));
	if (prev)
		prev->next = new_env;
	else if (!prev && i == 1)
		*tree->head = new_env;
	create_newenv(tokens, tree->head, cmds, new_env);
}

int	add_or_append(char **cmds, t_token_tree *tree,
	char **tokens, int i)
{
	char		*env_name;
	t_env_vars	*prev;

	prev = NULL;
	if (cmds[0][0] != '+' && ft_strchr(cmds[0], '+'))
	{
		env_name = ft_strtrim(cmds[0], "+"); //leaks
		if (!env_name && errno == ENOMEM)
			return (free_2d_array(cmds), ft_close(tokens, tree->head, tree),
				exit(1), -1);
		append_env_var(env_name, cmds[1], cmds, tree);
		free(env_name);
	}
	else if (ft_isalpha_quotes(cmds[0][0]) && is_string(cmds[0]))
	{
		prev = search_for_env_var(tree->head, cmds[0]);
		if (prev)
			check_exesting(prev, cmds, tokens, tree);
		else
			lst_add_element(tokens, cmds, tree, i);
	}
	else
		return (-1);
	return (0);
}

int	add_env_var(char **tokens, int nbr_envs, t_env_vars **head, t_token_tree *tree)
{
	int		i;
	char	**cmds;
	t_env_vars	*tmp;

	i = 1;
	cmds = NULL;
	tmp = search_for_env_var(tree->head, "?");
	while (i <= nbr_envs)
	{
    	cmds = ft_split_one(tokens[i], '=');
		if (!cmds && errno == ENOMEM)
			return (ft_close(tokens, head, tree), exit(1), -1);
		if (add_or_append(cmds, tree, tokens, i) == -1)
		{
			define_exit_status(tmp, "1");
			if (tokens[i][0] == '-')
				return (free_2d_array(cmds), invalid_option_error(tokens, i));
			return (print_err("export: `", tokens[i],
				"': not a valid identifier\n"), free_2d_array(cmds), -1);
		}
		free_2d_array(cmds);
		i++;
	}
	return (0);
}
