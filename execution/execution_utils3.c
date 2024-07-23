/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:10:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 12:21:53 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	exit_execve(int status, t_env_vars **head, char *path)
{
	t_env_vars	*tmp;

	tmp = search_for_env_var(head, "?");
	free(tmp->env_val);
	if (WTERMSIG(status) > 0)
		tmp->env_val = ft_itoa(128 + WTERMSIG(status));
	else
		tmp->env_val = ft_itoa(WEXITSTATUS(status));
	if (WEXITSTATUS(status) == 126)
		return (print_err("minishell: ", path, " : No such file or directory\n")
			, free(path), -1);
	else
		return (free(path), -1);
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	free(path);
	return (0);
}
