/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/17 17:09:44 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

int	handle_tokens(char **input, char *input_cpy, char **holder, int i)
{
	if (ft_strncmp("&&", *input, 2) == 0)
		holder[i] = get_token(input, 2, "&&");
	else if (ft_strncmp("||", *input, 2) == 0)
		holder[i] = get_token(input, 2, "||");
	else if (ft_strncmp("|", *input , 1) == 0)
		holder[i] = get_token(input, 1, "|");
	else if (ft_strncmp("(", *input , 1) == 0)
		holder[i] = get_token(input, 1, "(");
	else if (ft_strncmp(")", *input , 1) == 0)
		holder[i] = get_token(input, 1, ")");
	else if (ft_strncmp(">", *input , 1) == 0)
		holder[i] = get_token(input, 1, ">");
	else if (ft_strncmp(">>", *input , 2) == 0)
		holder[i] = get_token(input, 2, ">>");
	else if (ft_strncmp("<", *input , 1) == 0)
		holder[i] = get_token(input, 1, "<");
	else if (ft_strncmp("<<", *input , 2) == 0)
		holder[i] = get_token(input, 2, "<<");
	else
	{
		if (handle_cmd(input, input_cpy, holder, i) == 0)
			return (0);
	}
	return (1);
}

int	scan_syntax(char **holder, int j)
{
	int i;

	i = 0;
	if ((set_token_type(holder[0]) == OPERATOR_T
		|| set_token_type(holder[0]) == REDIRECTION_T)
		|| (set_token_type(holder[j - 1]) == OPERATOR_T
		|| set_token_type(holder[j - 1]) == REDIRECTION_T))
		return (0);
	while(holder[i] != NULL)
	{
		if (holder[i + 1]
			&& (set_token_type(holder[i]) == OPERATOR_T || set_token_type(holder[i]) == REDIRECTION_T)
			&& (set_token_type(holder[i + 1]) == OPERATOR_T || set_token_type(holder[i + 1]) == REDIRECTION_T))
			return (0);
		i++;
	}
	return (1);
}

int	has_wildcard(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && is_inside_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}
