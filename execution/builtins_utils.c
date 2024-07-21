/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:33:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 14:15:58 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int delete_env(t_env_vars **head, char *cmd, t_token_tree *tree, char **cmds)
{
    t_env_vars  *tmp;

	tmp = *head;
	if (!ft_isalpha(cmd[0]))
		return (print_err("minishell: unset: `", cmd, "': is not a valid identifier\n") , -1);
	else if (tmp && !ft_strcmp(tmp->env_name, cmd))
        delete_env_head(tmp, head);
	else
		delete_env_inside(tmp, cmd, cmds, tree);
    return (0);
}

int    print_echo_content(char **cmds, int i, int new_line)
{
    new_line = 1;
    while (cmds[i])
    {
        while (cmds[i] && cmds[i][0] == '-' && check_minus_n(cmds[i]) == 0)
        {
            new_line = 0;
            i++;
        }
        if (cmds[i])
        {
            ft_putstr_fd(cmds[i], 1);
            if (cmds[i + 1])
                ft_putchar_fd(' ', 1);
            i++;
        }
        else
            break;
    }
    if (new_line)
		ft_putchar_fd('\n', 1);
	return (1);
}

void    replace_nodes_content(t_env_vars *node1, t_env_vars *node2, t_token_tree *tree, char **cmds)
{
    free(node1->env_name);
    free(node1->env_val);
    node1->env_name = ft_strdup(node2->env_name);
    if (!node1->env_name)
        return (ft_close(cmds, tree->head, tree), exit(1));
    node1->env_val = ft_strdup(node2->env_val);
    node1->next = node2->next;
    free(node2->env_name);
    free(node2->env_val);
    free(node2);
}
