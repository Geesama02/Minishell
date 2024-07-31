/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:10:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/31 14:22:47 by maglagal         ###   ########.fr       */
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

void	update_oldpwd(char *current_dir, char **cmds, t_token_tree *tree)
{
	t_env_vars	*oldpwd;

	oldpwd = search_for_env_var(tree->head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->env_val);
		oldpwd->env_val = ft_strdup(current_dir);
		if (!oldpwd->env_val && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), exit(1));
	}
}

int	changing_current_directory(char **cmds, char *path, t_token_tree *tree)
{
	char		current_dir[PATH_MAX];
	char		*err_oldpwd;

	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		if (errno == ENOENT)
		{
			err_oldpwd = getenv("OLDPWD");
			if (!err_oldpwd)
				chdir("/");
			else
				chdir(err_oldpwd);
		}
		return (print_err(strerror(errno), "\n", NULL), -1);
	}
	if (chdir(path) == -1)
	{
		print_err("minishell: cd: ", path, ": ");
		return (print_err(strerror(errno), "\n", NULL), -1);
	}
	update_oldpwd(current_dir, cmds, tree);
	return (0);
}

int	count_linkedlist_size(t_env_vars *lst)
{
	int			counter;
	t_env_vars	*current;

	if (!lst)
		return (0);
	counter = 0;
	current = lst;
	while (current)
	{
		counter++;
		current = current->next;
	}
	return (counter);
}
