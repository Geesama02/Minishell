/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:29:13 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 17:45:06 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	*check_allocation(t_list *newL, t_list *temp, void (*del)(void *))
{
	while (newL != NULL)
	{
		temp = newL;
		newL = newL->next;
		del(temp->content);
		free(temp);
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*newtail;
	t_list	*newnode;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	newl = NULL;
	newtail = NULL;
	temp = NULL;
	while (lst != NULL)
	{
		newnode = (t_list *)malloc(sizeof(t_list));
		if (!newnode)
			return (check_allocation(newl, temp, del));
		newnode->content = f(lst->content);
		newnode->next = NULL;
		if (newl == NULL)
			newl = newnode;
		else
			newtail->next = newnode;
		newtail = newnode;
		lst = lst->next;
	}
	return (newl);
}
