/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:01:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 10:52:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    alloc_newstr_re(char *str, char *new_str)
{
    int i;
    int b;

    i = 0;
    b = 0;
    while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			new_str[b] = str[i];
			b++;
		}
		i++;
	}
    new_str[b] = '\0';
}

int redirec_edge_case(t_token_tree *tree, char **cmds)
{
    int fd;

    if (expand_filenames(tree->left->right) == -1)
        return (define_exit_status(*tree->head, "1"), -1);
    fd = open(ignore_quotes(&tree->left->right->token), O_RDONLY);
    if (fd == -1)
        return (print_err("minishell: ", tree->left->right->token, ": "), print_err(strerror(errno), "\n", NULL),
            define_exit_status(*tree->head, "1"), -1);
    else
        safe_close(fd, tree);
    if (execute_redirection(tree, cmds) == -1)
        return (-1);
    return (0);
}
