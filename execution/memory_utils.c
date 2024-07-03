/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:16:25 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/03 11:03:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    free_envs(t_env_vars **head)
{
	t_env_vars	*tmp;

	tmp = NULL;
	while (head && *head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (*head && ft_strcmp((*head)->env_name, "?") == 0)
			*head = (*head)->next;
		free(tmp->env_name);
		free(tmp->env_val);
		free(tmp);
	}
}

void	free_cmds(char **cmds)
{
	while (cmds && *cmds)
	{
		free(*cmds);
		cmds++;
	}
}

void	ft_close(t_env_vars **tmp, char **cmds, t_env_vars **head)
{
	// (void)tmp;
	// free((*tmp)->env_name);
	if (tmp && *tmp)
	{
		free((*tmp)->env_val);
		free(*tmp);	
	}
	free_cmds(cmds);
	free_envs(head);
}
