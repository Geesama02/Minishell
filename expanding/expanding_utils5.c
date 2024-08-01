/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:04:57 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/01 16:18:31 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_plus_op(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] && i > 0 && string[i] == '+'
			&& string[i + 1] == '\0' && string[i - 1] != '+')
			return (0);
		i++;
	}
	return (-1);
}

void	reset_terminal(struct termios *old_term, t_env_vars **head)
{
	if (tcsetattr(0, TCSANOW, old_term) == -1)
	{
		ft_close(NULL, head, NULL);
		print_err(strerror(errno), "\n", NULL);
		exit(1);
	}
}

int	handle_bad_wildcard(t_token_array *token_array)
{
	if (errno == ENOMEM)
		return (free_token_array(token_array), exit(1), 0);
	return (free_token_array(token_array), 0);
}
