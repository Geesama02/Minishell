/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:46:33 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 14:55:18 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	while (s[i])
	{
		if (c2 == s[i])
			return ((char *)(s + i));
		i++;
	}
	if (c2 == '\0')
		return ((char *)(s + i));
	return (NULL);
}
