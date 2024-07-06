/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:36:55 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:07 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*pntr;
	size_t	i;

	i = 0;
	pntr = malloc(count * size);
	if (!pntr)
		return (NULL);
	while (i < count * size)
	{
		pntr[i] = '\0';
		i++;
	}
	return (pntr);
}
