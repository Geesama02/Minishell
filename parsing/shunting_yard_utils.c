/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:46:54 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/22 09:40:52 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	count_array(t_token_array *tokens)
{
	int i;

	i = 0;
	while(tokens[i].token)
		i++;
	return (i);
}