/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:27:40 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:43 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*alloc_clear(t_list *new_list, void (*del)(void *))
{
	ft_lstclear(&new_list, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*node;

	new_list = NULL;
	new_node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		node = malloc(sizeof(t_list));
		if (!node)
			return (alloc_clear(new_list, del));
		node->content = f(lst->content);
		node->next = NULL;
		if (!new_list)
			new_list = node;
		else
			new_node->next = node;
		new_node = node;
		lst = lst->next;
	}
	return (new_list);
}
