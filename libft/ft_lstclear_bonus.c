/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:22:01 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:33 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	list = *lst;
	while (list != NULL)
	{
		temp = list;
		del(temp->content);
		list = list->next;
		free(temp);
	}
	*lst = NULL;
}
