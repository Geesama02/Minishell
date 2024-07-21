/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:53:19 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 10:33:16 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    safe_close(int fd, t_token_tree *node)
{
    if (close(fd) == -1)
    { 
        ft_close(NULL, node->head, node->tree_head_address);
        print_err("close() failed!!\n", NULL, NULL);
        exit(1);
    }
}

char    **ignore_quotes_2d_array(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
    {
        strs[i] = ignore_quotes(&strs[i]);
        i++;
    }
    return (strs);
}

int invalid_option_error(char **tokens, int i)
{
    print_err("minishell: export: ", NULL, NULL);
    ft_putchar_fd(tokens[i][0], 2);
    ft_putchar_fd(tokens[i][1], 2);
    print_err(": invalid option\nexport: usage: export [-nf] [name[=value] ...] or export -p\n", NULL, NULL);
    return (-1);
}

void    handle_fork_failure(t_token_tree *tree)
{
    print_err("fork function failed!!\n", NULL, NULL);
    ft_close(NULL, tree->head, tree->tree_head_address);
    exit(1);
}
