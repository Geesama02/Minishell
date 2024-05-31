/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/29 14:22:33 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

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
	else if (ft_strncmp(">>", *input , 2) == 0)
		holder[i] = get_token(input, 2, ">>");
	else if (ft_strncmp(">", *input , 1) == 0)
		holder[i] = get_token(input, 1, ">");
	else if (ft_strncmp("<<", *input , 2) == 0)
		holder[i] = get_token(input, 2, "<<");
	else if (ft_strncmp("<", *input , 1) == 0)
		holder[i] = get_token(input, 1, "<");
	else
	{
		if (handle_cmd(input, input_cpy, holder, i) == 0)
			return (0);
	}
	return (1);
}

int	scan_syntax(char **holder, char *input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(holder[j])
		j++;
	if ((set_token_type(holder[0]) == OPERATOR_T
		|| set_token_type(holder[0]) == REDIRECTION_I
		|| set_token_type(holder[0]) == REDIRECTION_O
		|| set_token_type(holder[0]) == REDIRECTION_A
		|| set_token_type(holder[0]) == HEREDOC)
		|| (set_token_type(holder[j - 1]) == OPERATOR_T
		|| set_token_type(holder[j - 1]) == HEREDOC
		|| set_token_type(holder[j - 1]) == REDIRECTION_I
		|| set_token_type(holder[j - 1]) == REDIRECTION_O
		|| set_token_type(holder[j - 1]) == REDIRECTION_A))
	{
		write_error("Error: parse error\n");
		return (0);
	}
	while(holder[i] != NULL)
	{
		if (has_wildcard(holder[i]))
		{
			if (handle_wildcard(&holder[i], input) == 0)
				return (0);
		}
		if (holder[i + 1]
			&& (set_token_type(holder[i]) == OPERATOR_T || set_token_type(holder[i]) == REDIRECTION_I
				|| set_token_type(holder[i]) == REDIRECTION_O || set_token_type(holder[i]) == REDIRECTION_A
				|| set_token_type(holder[i]) == HEREDOC)
			&& (set_token_type(holder[i + 1]) == OPERATOR_T || set_token_type(holder[i + 1]) == REDIRECTION_O
				|| set_token_type(holder[i + 1]) == REDIRECTION_I || set_token_type(holder[i + 1]) == REDIRECTION_A
				|| set_token_type(holder[i + 1]) == HEREDOC))
		{
			write_error("Error: parse error\n");
			printf("holder => %s\n", holder[i]);
			printf("holder + i => %s\n", holder[i + 1]);
			return (0);
		}
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

int	free_2d_array(char **array)
{
	int i;

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

int	handle_wildcard(char **str, char *input)
{
	char **sep_str;

	sep_str = ft_split(*str, ' ');
	if (!sep_str)
		return (0);
	free(*str);
	*str = ft_strdup("");
	if(!join_wildcard(sep_str, str, input))
		return (0);
	free_2d_array(sep_str);
	return (1);
} 
