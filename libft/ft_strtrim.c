/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:22:29 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:53:38 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_setchar(char s, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (s == set[j])
			return (1);
		j++;
	}
	return (0);
}

static void	counter(char const *s1, char const *set, int *j, int *i)
{
	while (s1[*j])
		(*j)++;
	while (is_setchar(s1[*i], set) && s1[*i])
		(*i)++;
	while (is_setchar(s1[--(*j)], set) && *j > *i)
		;
}

static char	*ft_alloc_zero(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_alloc_zero());
	counter(s1, set, &j, &i);
	str = malloc(j - i + 2);
	if (!str)
		return (NULL);
	while (i <= j)
		str[l++] = s1[i++];
	str[l] = '\0';
	return (str);
}
