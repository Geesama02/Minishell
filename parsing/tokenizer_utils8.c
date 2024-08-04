/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:49:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/03 10:04:17 by oait-laa         ###   ########.fr       */
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

char *get_second_cmd(char *holder)
{
	int	i;

	i = 0;
	while(holder[i])
	{
		if (holder[i + 1] && holder[i] == ' ' && holder[i + 1] != ' ' && is_inside_quotes(holder, i) == 0)
			return (holder + i + 1);
		i++;
	}
	return (holder);
}

void	swap_redirection_op(t_token_array *tmp_a_o, int i, int l, t_token_array *token_array)
{
	if (tmp_a_o && i > 0)
		swap_redirections(tmp_a_o - 1,
			find_redirection_double(token_array, l, i) - 1);
}