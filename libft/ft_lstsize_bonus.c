/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:50:59 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/08 18:14:07 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*current;

	if (!lst)
		return (0);
	counter = 0;
	current = lst;
	while (current)
	{
		counter++;
		current = current->next;
	}
	return (counter);
}
