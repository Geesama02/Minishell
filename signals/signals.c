/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:24 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/08 11:27:48 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	reset_terminal(struct termios *old_term, t_env_vars **head)
{
	if (tcsetattr(0, TCSANOW, old_term) == -1 && errno != ENOTTY)
	{
		ft_close(NULL, head, NULL);
		print_err(strerror(errno), "\n", NULL);
		exit(1);
	}
}

void	handle_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_is_heredoc[1] = 1;
		if (g_is_heredoc[0] == 1)
		{
			close(0);
			return ;
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	define_signals(void)
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
