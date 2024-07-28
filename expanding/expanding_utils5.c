/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:04:57 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/28 16:08:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_plus_op(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] && i > 0 && string[i] == '+'
			&& string[i + 1] == '\0' && string[i - 1] != '+')
			return (0);
		i++;
	}
	return (-1);
}
