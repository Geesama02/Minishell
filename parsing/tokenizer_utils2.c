/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 16:36:23 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	handle_tokens(char **input, char *input_cpy, char **holder, int i)
{
	if (ft_strncmp("&&", *input, 2) == 0)
		holder[i] = get_token(input, 2, "&&");
	else if (ft_strncmp("||", *input, 2) == 0)
		holder[i] = get_token(input, 2, "||");
	else if (ft_strncmp("|", *input, 1) == 0)
		holder[i] = get_token(input, 1, "|");
	else if (ft_strncmp("(", *input, 1) == 0)
		holder[i] = get_token(input, 1, "(");
	else if (ft_strncmp(")", *input, 1) == 0)
		holder[i] = get_token(input, 1, ")");
	else if (ft_strncmp(">>", *input, 2) == 0)
		holder[i] = get_token(input, 2, ">>");
	else if (ft_strncmp(">", *input, 1) == 0)
		holder[i] = get_token(input, 1, ">");
	else if (ft_strncmp("<<", *input, 2) == 0)
		holder[i] = get_token(input, 2, "<<");
	else if (ft_strncmp("<", *input, 1) == 0)
		holder[i] = get_token(input, 1, "<");
	else
	{
		if (handle_cmd(input, input_cpy, holder, i) == 0)
			return (0);
	}
	return (1);
}

int	scan_syntax(char **holder)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (holder[j])
		j++;
	if (is_operand(holder[0]) || is_operand(holder[j - 1]))
		return (write_error("Error: parse error\n"), 0);
	while (holder[i] != NULL)
	{
		if (has_wildcard(holder[i]))
		{
			if (handle_wildcard(&holder[i]) == 0)
				return (0);
		}
		if (holder[i + 1] && is_operand(holder[i]) && is_operand(holder[i + 1]))
			return (write_error("Error: parse error\n"), 0);
		i++;
	}
	return (1);
}

int	has_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && is_inside_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

int	handle_wildcard(char **str)
{
	char	**sep_str;

	sep_str = ft_split(*str, ' ');
	if (!sep_str)
		return (0);
	free(*str);
	*str = ft_strdup("");
	if (!*str)
		return (free_2d_array(sep_str), 0);
	if (!join_wildcard(sep_str, str))
		return (0);
	free_2d_array(sep_str);
	return (1);
}
