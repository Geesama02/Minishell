/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:46:53 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 14:00:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

void    eof_pressed(t_env_vars **head)
{
	t_env_vars	*tmp;
	int			exit_s;

	exit_s = 0;
	tmp = search_for_env_var(head, "?");
	if (tmp)
		exit_s = ft_atoi(tmp->env_val);
	rl_clear_history();
	write(0, "exit\n", 5);
	ft_close(NULL, head, NULL);
	if (g_is_heredoc[1] == 1)
		exit(1);
	exit(exit_s);
}
