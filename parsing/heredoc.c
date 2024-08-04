/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:07:18 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/04 09:48:54 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	count_heredoc_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] != ' ' || (input[i] != ' '
				&& is_inside_quotes(input, i) == 0)) && (!is_op(input + i)
			|| (is_op(input + i) && is_inside_quotes(input, i))))
		i++;
	return (i);
}

int	has_more_cmds(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' '
			&& is_inside_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_str_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			check_between_quotes(str, &i, &count, '\'');
			continue ;
		}
		else if (str[i] == '\"')
		{
			check_between_quotes(str, &i, &count, '\"');
			continue ;
		}
		else
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

void	skip_quotes(char *str_original, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str_original[i])
	{
		if (str_original[i] == '\'')
		{
			i++;
			while (str_original[i] && str_original[i] != '\'')
				new[j++] = str_original[i++];
		}
		else if (str_original[i] == '\"')
		{
			i++;
			while (str_original[i] && str_original[i] != '\"')
				new[j++] = str_original[i++];
		}
		else
			new[j++] = str_original[i];
		if (str_original[i])
			i++;
	}
	new[j] = '\0';
}

char	*ignore_quotes(char **str)
{
	// int		len;
	char	*tmp;

	if (!*str)
		return (NULL);
	// len = ft_strlen(*str) - 1;
	// while (len >= 0 && *(*str + len) == ' ')
	// {
	// 	*(*str + len) = '\0';
	// 	len--;
	// }
	tmp = malloc(count_str_len(*str) + 1);
	if (!tmp)
		return (NULL);
	skip_quotes(*str, tmp);
	free(*str);
	*str = tmp;
	return (*str);
}
