/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:25:41 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:27 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!new || !lst)
		return ;
	list = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = new;
	}
}
