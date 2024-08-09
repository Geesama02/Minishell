/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:22:25 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/09 16:11:27 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	count_inside_quote(char *str, int i, int *count, char quote)
{
	i++;
	(*count)++;
	while ((str[i] != quote) && (str[i]))
	{
		(*count)++;
		i++;
	}
	if (str[i])
		i++;
	(*count)++;
}

int	count_str_len_qt(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i] == '\'')
	{
		count_inside_quote(str, i, &count, '\'');
	}
	else if (str[i] == '\"')
	{
		count_inside_quote(str, i, &count, '\"');
	}
	else
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			count++;
			(i)++;
		}
	}
	return (count);
}

char	*alloc_new_str(char *str, int *i)
{
	char	*tmp;
	int		len;
	int		j;

	len = 0;
	j = 0;
	len = count_str_len_qt(str, *i);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (j < len)
	{
		tmp[j] = str[*i];
		(*i)++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	if_must_add(int j, char **tmp, char nxt)
{
	char	*tmp2;

	if (tmp[j][ft_strlen(tmp[j]) - 1] == '$' && (nxt == '\'' || nxt == '\"'))
	{
		tmp2 = tmp[j];
		if (nxt == '\"')
			tmp[j] = ft_strjoin(tmp2, "\"");
		else
			tmp[j] = ft_strjoin(tmp2, "'");
		if (!tmp[j])
			return (0);
		free(tmp2);
	}
	return (1);
}

void	long_error(void)
{
	print_err("cd: error retrieving current",
		" directory: getcwd: cannot access parent directories: ", NULL);
	print_err(strerror(errno), "\n", NULL);
}
