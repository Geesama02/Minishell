/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:43:51 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/16 17:51:00 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	must_reorder(t_token_array *token_array)
{
	int	i;

	i = 0;
	while (token_array[i].token)
	{
		if (is_redirection(token_array[i].type) && (i == 0 || token_array[i - 1].type == OPERATOR_T))
			return (1);
		i++;
	}
	return (0);
}

void	fill_new_token(t_token_array *tmp, char *extra, int n, int l)
{
	if (l == n)
	{
		tmp[l].token = extra;
		tmp[l].type = CMD_T;
	}
}

int	count_len(t_token_array *token_array)
{
	int	i;

	i = 0;
	while(token_array[i].token)
		i++;
	return (i);
}

t_token_array	*realloc_tokens(t_token_array *token_array, int n, char *extra)
{
	t_token_array *tmp;
	int	c;
	int l;
	int	i;

	c = count_len(token_array);
	i = 0;
	l = 0;
	tmp = malloc(sizeof(t_token_array) * (c + 2));
	if (!tmp)
		return (NULL);
	while (token_array[i].token)
	{
		fill_new_token(tmp, extra, n, l);
		if (l != n)
		{
			tmp[l].token = token_array[i].token;
			tmp[l].type = token_array[i++].type;
		}
		l++;
	}
	tmp[l].token = NULL;
	free(token_array);
	return (tmp);
}

int	reorder_tokens(t_token_array **token_array)
{
	int	i;
	char	*tmp_holder;
	t_token_array *tmp;
	t_token_array *holder;

	i = 0;
	holder = *token_array;
	while (holder[i].token)
	{
		if (is_redirection(holder[i].type) && (i == 0 || holder[i - 1].type == OPERATOR_T))
		{
			tmp_holder = ft_split_first(holder[i + 1].token);
			if (!tmp_holder)
				return (free_token_array(*token_array), exit(1), 0);
			tmp = realloc_tokens(holder, i, tmp_holder);
			if (!tmp)
				return (free(tmp_holder), free_token_array(*token_array), exit(1), 0);
			holder = tmp;
			*token_array = holder;
		}
		i++;
	}
	return (0);
}
