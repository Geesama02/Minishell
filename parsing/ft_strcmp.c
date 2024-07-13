/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:51:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/13 13:52:48 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	str1;
	unsigned char	str2;

	// if(!s1 || !s2)
	// 	return (1);
	while ((*s1 || *s2))
	{
		str1 = (unsigned char)*s1;
		str2 = (unsigned char)*s2;
		if (str1 != str2)
			return (str1 - str2);
		s1++;
		s2++;
	}
	return (0);
}
