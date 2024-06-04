/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:33:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/06/03 17:50:02 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    print_echo_content(char **cmds, int i, int new_line)
{
    while (cmds[i])
    {
        ft_putstr(cmds[i]);
        if (cmds[i + 1])
            ft_putchar(' ');
        i++;
    }
    if (new_line)
		ft_putchar('\n');
}

void    ft_putstr(char *str)
{
    if (!str)
    {
        ft_putchar('\n');
        ft_putchar('\n');
    }
    else
    {
        while (*str)
        {
            ft_putchar(*str);
            str++;
        }
    }
}

void    replace_nodes_content(t_env_vars *node1, t_env_vars *node2)
{
    node1->env_name = node2->env_name;
    node1->env_val = node2->env_val;
    node1->next = node2->next;
    free(node2);
}
