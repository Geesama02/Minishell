/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:33:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 09:21:55 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int    print_echo_content(char **cmds, int i, int new_line)
{
	char	*tmp;
	
    while (cmds[i])
    {
        new_line = 1;
        while (cmds[i] && !check_minus_n(cmds[i]))
        {
            new_line = 0;
            i++;
        }
        if (cmds[i])
        {
            tmp = ignore_quotes(&cmds[i]);
            if (!tmp)
                return (0);
            ft_putstr(tmp);
            if (cmds[i + 1])
                ft_putchar(' ');
            i++;
        }
        else
            break;
    }
    if (new_line)
		ft_putchar('\n');
	return (1);
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
    free(node1->env_name);
    free(node1->env_val);
    node1->env_name = ft_strdup(node2->env_name);
    node1->env_val = ft_strdup(node2->env_val);
    node1->next = node2->next;
    free(node2->env_name);
    free(node2->env_val);
    free(node2);
}
