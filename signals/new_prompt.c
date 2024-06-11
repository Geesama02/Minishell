/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:24 by maglagal          #+#    #+#             */
/*   Updated: 2024/06/11 10:02:32 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	handle_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		if (is_heredoc == 1)
		{
			// rl_done = 1;
			return ;
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	define_signals()
{
	struct sigaction	sa1;
	sigset_t			set;

	sigemptyset(&set);
	// sigaddset(&set, SIGINT);
	sa1.sa_handler = handle_new_prompt;
	// sa1.sa_flags = SA_RESTART;
	sa1.sa_mask = set;
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa1, NULL);
}
