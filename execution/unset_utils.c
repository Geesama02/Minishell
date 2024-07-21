/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 09:29:37 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 09:38:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    delete_env_head(t_env_vars *tmp, t_env_vars **head)
{
    if (tmp->next)
        *head = tmp->next;
    else
        *head = NULL;
    free_node(tmp);
}

void    delete_env_inside(t_env_vars *tmp, char *cmd,
    char **cmds, t_token_tree *tree)
{
    while (tmp && tmp->next && ft_strcmp(tmp->next->env_name, cmd))
        tmp = tmp->next;
    if (tmp && tmp->next && tmp->next->next)
        replace_nodes_content(tmp->next, tmp->next->next, tree, cmds);
    else if (tmp && tmp->next && !tmp->next->next)
    {
        free_node(tmp->next);
        tmp->next = NULL;
    }
}
