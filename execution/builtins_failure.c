/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_failure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:32:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/08 17:26:53 by maglagal         ###   ########.fr       */
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
