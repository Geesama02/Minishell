/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:43:51 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/19 10:22:37 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	must_reorder(char **holder)
{
	int	i;

	i = 0;
	while (holder[i])
	{
		if (is_redirection_heredoc(holder[i]) && (i == 0 || set_token_type(holder[i - 1]) == OPERATOR_T))
			return (1);
		i++;
	}
	return (0);
}

int	count_len(char **holder)
{
	int	i;

	i = 0;
	while(holder[i])
		i++;
	return (i);
}

// char *ft_split_first_token(char *str)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	str[i] = '\0';
// 	tmp = ft_strdup(str + i + 1);
// 	return (tmp);
// }

char	**realloc_tokens(char **holder, int n, char *extra)
{
	char **tmp;
	int	c;
	int l;
	int	i;

	c = count_len(holder);
	i = 0;
	l = 0;
	tmp = malloc(sizeof(char *) * (c + 2));
	if (!tmp)
		return (NULL);
	while (holder[i])
	{
		if (l == n)
			tmp[l] = extra;
		else
			tmp[l] = holder[i++];
		l++;
	}
	tmp[l] = NULL;
	free(holder);
	return (tmp);
}

int	reorder_tokens(char ***holder)
{
	int	i;
	char	*tmp_holder;
	char **tmp;
	char **new_holder;

	i = 0;
	new_holder = *holder;
	while (new_holder[i])
	{
		if (is_redirection_heredoc(new_holder[i]) && (i == 0 || set_token_type(new_holder[i - 1]) == OPERATOR_T))
		{
			tmp_holder = ft_split_first(new_holder[i + 1]);
			if (!tmp_holder)
				return (free_2d_array(*holder), exit(1), 0);
			tmp = realloc_tokens(new_holder, i, tmp_holder);
			if (!tmp)
				return (free(tmp_holder),  exit(1), 0);
			new_holder = tmp;
			*holder = new_holder;
		}
		i++;
	}
	return (0);
}
