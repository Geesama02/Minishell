/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:49:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/02 20:40:09 by oait-laa         ###   ########.fr       */
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
