/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:44:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/07 13:45:04 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    env_command(t_env_vars *env_vars)
{
	while (env_vars)
	{
		if (env_vars->env_val && env_vars->env_name[0] != '?')
			printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
		env_vars = env_vars->next;
	}
}

void    exit_command(char **cmds, t_env_vars **head)
{
    write(1, "exit\n", 6);
    ft_close(cmds, head);
    free(cmds);
    exit(0);
}
