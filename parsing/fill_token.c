/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:06 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/05 17:04:22 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	swap_tospace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\t' || input[i] == '\n')
			input[i] = ' ';
		i++;
	}
}

int	unclosed_var(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int	has_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*remove__quotes(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	if (unclosed_var(str, '\"') == 1 || unclosed_var(str, '\'') == 1)
	{
		write_error("Error: quotes not closed\n");
		return (NULL);
	}
	else if (has_quotes(str, '\"') == 0)
	{
		tmp = ft_strtrim(str, "\"");
		free(str);
		return (tmp);
	}
	else if (has_quotes(str, '\'') == 0)
	{
		tmp = ft_strtrim(str, "\'");
		free(str);
		return (tmp);
	}
	return (str);
}
