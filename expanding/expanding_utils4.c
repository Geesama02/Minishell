/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:57:37 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 11:58:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    null_terminating_rev(char *string)
{
	int	len;

	len = ft_strlen(string);
	while (len >= 0 && string[len - 1] == ' ')
	{
		string[len - 1] = '\0';
		len--;
	}
}
