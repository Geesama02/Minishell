/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:49:36 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/12 12:54:11 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	if_must_reverse(t_token_array *token_array, int i, int l, int j)
{
	return (is_redirection_heredoc(token_array[j].token)
		&& is_redirection_heredoc(token_array[i - l - 1].token));
}
