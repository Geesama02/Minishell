/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:49:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/04 15:54:55 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	join_extra_with_redi(char **holder, int i)
{
	char	*extra;
	char	*tmp;

	extra = ft_split_first(holder[i + 1]);
	if (!extra)
		return (free_2d_array(holder), exit(1), 0);
	tmp = holder[i - 1];
	holder[i - 1] = ft_strjoin(tmp, extra);
	if (!holder[i - 1])
		return (free(extra),
			free_2d_array(holder), exit(1), 0);
	free(tmp);
	free(extra);
	return (0);
}

char	*get_second_cmd(char *holder)
{
	int	i;

	i = 0;
	while (holder[i])
	{
		if (holder[i + 1] && holder[i] == ' ' && holder[i + 1] != ' '
			&& is_inside_quotes(holder, i) == 0)
			return (holder + i + 1);
		i++;
	}
	return (holder);
}

void	swap_redirection_op(t_token_array *tmp_a_o, int i, int l,
			t_token_array *token_array)
{
	if (tmp_a_o && i > 0)
		swap_redirections(tmp_a_o - 1,
			find_redirection_double(token_array, l, i) - 1);
}

int	alloc_str_no_qt(int j, t_token_tree *tree, char **tmp, char nxt)
{
	if (!tmp[j])
		return (0);
	if (has_vars(tmp[j]))
	{
		tmp[j] = ignore_quotes(&tmp[j]);
		if (!tmp[j])
			return (0);
		if (!if_must_add(j, tmp, nxt))
			return (0);
		tmp[j] = expand_vars(tmp[j], *tree->head);
		if (!tmp[j])
			return (0);
	}
	else
	{
		tmp[j] = ignore_quotes(&tmp[j]);
		if (!tmp[j])
			return (0);
	}
	return (1);
}

void	remove_empty_space(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len >= 0 && *(str + len) == ' ')
	{
		*(str + len) = '\0';
		len--;
	}
}
