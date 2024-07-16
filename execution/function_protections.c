/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:53:19 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 15:21:54 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

// int safe_close(int fd, t_token_tree *node)
// {
//     if (close(fd) == -1)
//     {    
//         print_err("close() failed!!\n", NULL, NULL);
//         return (-1);
//     }
//     return (0);
// }

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
