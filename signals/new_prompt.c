/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:24 by maglagal          #+#    #+#             */
/*   Updated: 2024/06/06 18:07:42 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

// void	reset_terminal_attr()
// {
// 	struct termios s_new;

// 	s_new.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | IXON);
// 	s_new.c_cc[VMIN] = 1;
// 	s_new.c_cc[VTIME] = 0;
// 	tcsetattr(0, TCSANOW, &s_new);
// }

void	handle_new_prompt(int signum)
{
	if (signum == SIGINT)
	{	
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
	sigaddset(&set, SIGINT);
	sa1.sa_handler = handle_new_prompt;
	sa1.sa_flags = SA_RESTART;
	sa1.sa_mask = set;
	sigaction(SIGINT, &sa1, NULL);
	sigaction(SIGQUIT, &sa1, NULL);
}
