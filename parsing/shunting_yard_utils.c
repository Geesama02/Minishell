/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:46:54 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 15:39:17 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	count_array(t_token_array *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
		i++;
	return (i);
}
