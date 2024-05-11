/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/10 15:07:30 by oait-laa         ###   ########.fr       */
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
