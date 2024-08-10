/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:43:51 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/10 10:45:44 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	must_reorder(char **holder)
{
	int	i;

	i = 0;
	while (holder[i])
	{
		if (is_redirection_heredoc(holder[i])
			&& (i == 0 || set_token_type(holder[i - 1]) == OPERATOR_T
				|| set_token_type(holder[i - 1]) == PARETHESIS_O))
			return (1);
		i++;
	}
	return (0);
}

int	count_len(char **holder)
{
	int	i;

	i = 0;
	while (holder[i])
		i++;
	return (i);
}

int	is_bad_syntax(char **holder, int i)
{
	return (holder[i + 1] && ((set_token_type(holder[i]) == OPERATOR_T
				&& set_token_type(holder[i + 1]) == OPERATOR_T)
			|| (is_redirection_heredoc(holder[i]) && is_operand(holder[i + 1]))
			|| (set_token_type(holder[i]) == PARETHESIS_O && i != 0
				&& set_token_type(holder[i - 1]) != OPERATOR_T)
			|| (set_token_type(holder[i]) == PARETHESIS_C
				&& !is_operand(holder[i + 1]))
			|| (set_token_type(holder[i]) == PARETHESIS_O
				&& set_token_type(holder[i + 1]) == PARETHESIS_C)
			|| (is_operand(holder[i])
				&& set_token_type(holder[i + 1]) == PARETHESIS_C)));
}

char	**realloc_tokens(char **holder, int n, char *extra)
{
	char	**tmp;
	int		c;
	int		l;
	int		i;

	c = count_len(holder);
	i = 0;
	l = 0;
	tmp = malloc(sizeof(char *) * (c + 2));
	if (!tmp)
		return (free_2d_array(holder), NULL);
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
	int		i;
	char	*tmp_holder;
	char	**tmp;
	char	**new_holder;

	i = 0;
	new_holder = *holder;
	while (new_holder[i])
	{
		if (is_redirection_heredoc(new_holder[i])
			&& (i == 0 || set_token_type(new_holder[i - 1]) == OPERATOR_T
				|| set_token_type(new_holder[i - 1]) == PARETHESIS_O))
		{
			tmp_holder = ft_split_first(new_holder[i + 1]);
			if (!tmp_holder)
				return (free_2d_array(*holder), exit(1), 0);
			tmp = realloc_tokens(new_holder, i, tmp_holder);
			if (!tmp)
				return (free(tmp_holder), exit(1), 0);
			new_holder = tmp;
			*holder = new_holder;
		}
		i++;
	}
	return (0);
}
