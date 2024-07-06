/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:03:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/06 10:41:09 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	*handle_other_tokens(t_token_array *token_array, char **holder,
	int *i, t_token_vars *vars)
{
	if (vars->x != -1)
	{
		vars->l++;
		vars->x = -1;
		vars->check = 0;
	}
	token_array[vars->l].token = ft_strdup(holder[*i]);
	if (!token_array[vars->l].token)
		return (free_token_holder(holder, token_array, vars->l),
			exit(1), NULL);
	token_array[vars->l].type = set_token_type(holder[*i]);
	(*i)++;
	if (has_vars(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token,
				vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				exit(1), NULL);
	}
	vars->l++;
	return (NULL);
}

char	*get_extra_chars(char *holder)
{
	int	i;

	i = 0;
	while (holder[i])
	{
		if (holder[0] == '?')
			return (holder + 1);
		if (non_var_name(holder[i]))
			return (holder + i);
		i++;
	}
	return (NULL);
}

int	tokenize(char **input, char *input_cpy, char **holder)
{
	int	i;
	char *cpy;

	i = 0;
	cpy = *input;
	while (**input)
	{
		while (**input == ' ')
			(*input)++;
		if (**input == '\0')
			break ;
		if (!handle_tokens(input, input_cpy, holder, i))
			return (0);
		i++;
	}
	holder[i] = NULL;
	free(cpy);
	return (1);
}

t_t_type	set_token_type(char *token)
{
	if (ft_strcmp("&&", token) == 0 || ft_strcmp("||", token) == 0
		|| ft_strcmp("|", token) == 0)
		return (OPERATOR_T);
	if (ft_strcmp(">>", token) == 0)
		return (REDIRECTION_A);
	if (ft_strcmp(">", token) == 0)
		return (REDIRECTION_O);
	if (ft_strcmp("<<", token) == 0)
		return (HEREDOC);
	if (ft_strcmp("<", token) == 0)
		return (REDIRECTION_I);
	if (ft_strcmp("(", token) == 0)
		return (PARETHESIS_O);
	if (ft_strcmp(")", token) == 0)
		return (PARETHESIS_C);
	return (CMD_T);
}

int	is_operand(char *str)
{
	return (set_token_type(str) == OPERATOR_T
		|| set_token_type(str) == REDIRECTION_I
		|| set_token_type(str) == REDIRECTION_O
		|| set_token_type(str) == REDIRECTION_A
		|| set_token_type(str) == HEREDOC);
}
