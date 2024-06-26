/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:25 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 22:10:04 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

char	*handle_multi_heredoc(t_token_array *token_array,
	char **holder, t_token_vars *vars, int i)
{
	char	*tmp;
	char	*token;

	tmp = ft_strdup(token_array[vars->x].token);
	if (!tmp)
		return (NULL);
	free(token_array[vars->x].token);
	if (vars->cmd_holder && token_array[vars->x].type == CMD_T)
	{
		token = continue_heredoc(ignore_quotes(holder[i + 1]), token_array, holder, &vars->l);
		if (!token)
			return (free(tmp), NULL);
		free(token);
		token = ft_strjoin(tmp, vars->cmd_holder);
	}
	else
	{
		token = continue_heredoc(ignore_quotes(holder[i + 1]), token_array, holder, &vars->l);
		if (!token)
			return (free(tmp), NULL);
		check_if_has_file(token_array, &token, vars, tmp);
	}
	free(tmp);
	return (token);
}

void	*handle_first_heredoc(t_token_array *token_array,
	char **holder, int *l, int i)
{
	token_array[*l].token = ft_strdup(holder[i]);
	if (!token_array[*l].token)
		return (NULL);
	token_array[*l].type = HEREDOC;
	(*l)++;
	token_array[*l].token = continue_heredoc(ignore_quotes(holder[i + 1]), token_array, holder, l);
	if (!token_array[*l].token)
		return (NULL);
	token_array[*l].type = HEREDOC_TOKEN;
	return (holder);
}

char	*set_extra_cmd(t_token_array *token_array,
	char **holder, int i, t_token_vars *vars)
{
	char	*tmp;

	tmp = NULL;
	if (i > 0 && (has_more_cmds(holder[i - 1]) || has_more_cmds(holder[i + 1])))
	{
		tmp = handle_extra_cmd(token_array, holder, &vars->check, i);
		if (!tmp)
			return (free_token_holder(holder, token_array, vars->l),
				exit(1), NULL);
	}
	else
		tmp = NULL;
	return (tmp);
}

int	fill_heredoc(t_token_array *token_array,
	char **holder, int i, t_token_vars *vars)
{
	if (vars->x != -1)
	{
		token_array[vars->x].token = handle_multi_heredoc(token_array,
				holder, vars, i);
		if (!token_array[vars->x].token)
			return (free_token_holder(holder, token_array, vars->l),
				exit(1), 0);
	}
	else
	{
		if (!handle_first_heredoc(token_array, holder, &vars->l, i))
			return (0);
		vars->x = vars->l;
		if (vars->cmd_holder)
		{
			free(token_array[vars->l].token);
			token_array[vars->l].token = ft_strdup(vars->cmd_holder);
			if (!token_array[vars->l].token)
				return (free_token_holder(holder, token_array, vars->l),
					exit(1), 0);
			token_array[vars->l].type = CMD_T;
		}
	}
	return (1);
}

int	handle_heredoc(t_token_array *token_array,
	char **holder, int *i, t_token_vars *vars)
{
	vars->cmd_holder = set_extra_cmd(token_array, holder, *i, vars);
	if (!fill_heredoc(token_array, holder, *i, vars))
		return (0);
	free(vars->cmd_holder);
	if (token_array[vars->l].type == HEREDOC_TOKEN
		&& has_vars_no_quotes(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token,
				vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				exit(1), 0);
	}
	else if (has_vars(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token,
				vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				exit(1), 0);
	}
	*i += 2;
	return (1);
}
