/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:10:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/26 14:26:27 by maglagal         ###   ########.fr       */
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
	if (WEXITSTATUS(status) == 127)
		return (print_err("minishell: ", path, " : No such file or directory\n")
			, free(path), -1);
	else if (WEXITSTATUS(status) == 1)
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit: 3\n", 9);
		return (free(path), -1);
	}
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	free(path);
	return (0);
}


int	changing_current_directory(char *path, t_env_vars *head)
{
	char		current_dir[PATH_MAX];
	t_env_vars	*oldpwd;

	if (!getcwd(current_dir, sizeof(current_dir)))
		return (print_err(strerror(errno), "\n", NULL), -1);
	if (chdir(path) == -1)
		return (print_err("minishell: cd: ", strerror(errno), "\n"), -1);
	oldpwd = search_for_env_var(&head, "OLDPWD");
	free(oldpwd->env_val);
	oldpwd->env_val = ft_strdup(current_dir);
	return (0);
}
