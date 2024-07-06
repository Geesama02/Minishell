/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:54:57 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 15:49:10 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>	

t_list	*ft_lstnew(void *content)
{
	t_list	*newn;

	newn = (t_list *)malloc(sizeof(t_list));
	if (!newn)
		return (NULL);
	if (!content)
		newn->content = NULL;
	else
		newn->content = content;
	newn->next = (0); 
	return (newn);
}
