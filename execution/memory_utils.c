/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:16:25 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 12:28:43 by maglagal         ###   ########.fr       */
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

void	ft_close(char **cmds, t_env_vars **head, t_token_tree *tree)
{
	free_2d_array(cmds);
	free_envs(head);
	free_tree(tree);
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
