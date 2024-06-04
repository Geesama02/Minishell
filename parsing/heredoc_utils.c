/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:25 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/31 15:36:37 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

char *handle_multi_heredoc(t_token_array *token_array, char *holder, t_token_vars *vars)
{
	char *tmp;
	char *token;

	tmp = ft_strdup(token_array[vars->x].token);
	free(token_array[vars->x].token);
	if (vars->cmd_holder && token_array[vars->x].type == CMD_T)
	{
		token = continue_heredoc(ignore_quotes(holder));
		free(token);
		token = ft_strjoin(tmp, vars->cmd_holder);
		free(tmp);
	}
	else
	{
		token = continue_heredoc(ignore_quotes(holder));
		if (vars->check)
		{
			free(token);
			if (vars->cmd_holder)
				token = ft_strdup(vars->cmd_holder);
			else
				token = ft_strdup(tmp);
			token_array[vars->x].type = CMD_T;
		}
		else
			token_array[vars->x].type = HEREDOC_TOKEN;
		free(tmp);
	}
	return (token);
}

void *handle_first_heredoc(t_token_array *token_array, char **holder, int *l, int i)
{
	token_array[*l].token = ft_strdup(holder[i]);
	if (!token_array[*l].token)
		return (NULL);
	token_array[*l].type = HEREDOC;
	(*l)++;
	token_array[*l].token = continue_heredoc(ignore_quotes(holder[i + 1]));
	// printf("here -> %s\n", token_array[*l].token);
	if (!token_array[*l].token)
		return (NULL);
	token_array[*l].type = HEREDOC_TOKEN;
	return (holder);
}

char *set_extra_cmd(t_token_array *token_array, char **holder, int i, t_token_vars *vars)
{
	char *tmp;

	tmp = NULL;
	if (i > 0 && (has_more_cmds(holder[i - 1]) || has_more_cmds(holder[i + 1])))
	{
		tmp = handle_extra_cmd(token_array, holder, &vars->check, i);
		if (!tmp)
			return (free_token_holder(holder, token_array, vars->l), free(vars->input), exit(1), NULL);
	}
	else
		tmp = NULL;
	return (tmp);
}

void *fill_heredoc(t_token_array *token_array, char **holder, int i, t_token_vars *vars)
{
	if (vars->x != -1)
	{
		token_array[vars->x].token = handle_multi_heredoc(token_array,
			 holder[i + 1], vars);
		if (!token_array[vars->x].token)
			return (free_token_holder(holder, token_array, vars->l),
				free(vars->input), exit(1), NULL);
	}
	else
	{
		if (!handle_first_heredoc(token_array, holder, &vars->l, i))
			return (free_token_holder(holder, token_array, vars->l),
				free(vars->input), exit(1), NULL);
		vars->x = vars->l;
		if (vars->cmd_holder)
		{
			free(token_array[vars->l].token);
			token_array[vars->l].token = ft_strdup(vars->cmd_holder);
			if (!token_array[vars->l].token)
				return (free_token_holder(holder, token_array, vars->l),
					free(vars->input), exit(1), NULL);
			token_array[vars->l].type = CMD_T;
		}
	}
	return (NULL);
}
void	*handle_heredoc(t_token_array *token_array, char **holder, int *i, t_token_vars *vars)
{
	vars->cmd_holder = set_extra_cmd(token_array, holder, *i, vars);
	fill_heredoc(token_array, holder, *i, vars);
	free(vars->cmd_holder);
	free(holder[*i]);
	free(holder[*i + 1]);
	if (token_array[vars->l].type == HEREDOC_TOKEN && has_vars_no_quotes(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token, vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				free(vars->input), exit(1), NULL);
	}
	else if (has_vars(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token, vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				free(vars->input), exit(1), NULL);
	}
	*i += 2;
	return (NULL);
}
