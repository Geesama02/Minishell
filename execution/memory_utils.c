/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:16:25 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 09:21:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    free_envs(t_env_vars **head)
{
	t_env_vars	*tmp;

	tmp = NULL;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->env_name);
		free(tmp->env_val);
		free(tmp);
	}
}

void	free_cmds(char **cmds)
{
	int i;

	i = 0;
	if (cmds)
	{
		while (cmds[i])
		{
			free(cmds[i]);
			i++;
		}
	}
}

void	ft_close(char **cmds, t_env_vars **head)
{
	free_2d_array(cmds);
	free_envs(head);
}

int	count_2d_array_elements(char **arr)
{
	int	counter;

	counter = 0;
	while (*arr)
	{	
		counter++;
		arr++;
	}
	return (counter);
}

void    free_node(t_env_vars *node)
{
    free(node->env_name);
    free(node->env_val);
    free(node);
}
