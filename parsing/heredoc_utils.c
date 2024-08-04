/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:25 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/04 17:16:44 by oait-laa         ###   ########.fr       */
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
	remove_empty_space(holder[i + 1]);
	token = continue_heredoc(ignore_quotes(&holder[i + 1]),
			token_array, holder, &vars->l);
	if (!token)
		return (free(tmp), NULL);
	if (vars->cmd_holder && token_array[vars->x].type == CMD_T)
	{
		free(token);
		token = ft_strjoin(tmp, vars->cmd_holder);
	}
	else
		check_if_has_file(token_array, &token, vars, tmp);
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
	remove_empty_space(holder[i + 1]);
	token_array[*l].token = continue_heredoc(ignore_quotes(&holder[i + 1]),
			token_array, holder, l);
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
				define_exit_status(vars->head, "1"), 0);
	}
	else
	{
		if (!handle_first_heredoc(token_array, holder, &vars->l, i))
			return (free_token_holder(holder, token_array, vars->l),
				define_exit_status(vars->head, "1"), 0);
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
	int	has_quote;

	has_quote = 0;
	vars->cmd_holder = set_extra_cmd(token_array, holder, *i, vars);
	if (!has_quotes(holder[*i + 1], '\'') || !has_quotes(holder[*i + 1], '\"'))
		has_quote = 1;
	if (!fill_heredoc(token_array, holder, *i, vars))
		return (0);
	free(vars->cmd_holder);
	handle_heredoc_expand(token_array, holder, has_quote, vars);
	*i += 2;
	return (1);
}
