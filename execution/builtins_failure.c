/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_failure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:32:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/13 08:59:16 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    handle_builtins_failure(t_env_vars **head, t_env_vars *tmp)
{
    free(tmp->env_val);
    tmp->env_val = ft_strdup("1");
    if (!tmp->env_val)
        return (free_envs(head));
}

void    print_err(char *string1, char *string2, char *string3)
{
    ft_putstr_fd(string1, 2);
    ft_putstr_fd(string2, 2);
    ft_putstr_fd(string3, 2);
}
