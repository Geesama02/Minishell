/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:10:11 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/08 15:15:08 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	exit_execve(int status, t_token_tree *tree, char *path, char **cmds)
{
	t_env_vars	*tmp;

	update_underscore_env(NULL, cmds, *tree->head, tree);
	tmp = search_for_env(tree->head, "?");
	free(tmp->env_val);
	if (WTERMSIG(status) > 0)
		tmp->env_val = ft_itoa(128 + WTERMSIG(status));
	else
		tmp->env_val = ft_itoa(WEXITSTATUS(status));
	if (WEXITSTATUS(status) == 127)
		return (free(path), -1);
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

	oldpwd = search_for_env(tree->head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->env_val);
		oldpwd->env_val = ft_strdup(current_dir);
		if (!oldpwd->env_val && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), exit(1));
	}
	else
	{
		oldpwd = malloc(sizeof(t_env_vars));
		if (!oldpwd && errno == ENOMEM)
			return (ft_close(cmds, tree->head, tree), exit(1));
		oldpwd->env_name = ft_strdup("OLDPWD");
		if (!oldpwd->env_name && errno == ENOMEM)
			return (free(oldpwd), ft_close(cmds, tree->head, tree), exit(1));
		oldpwd->env_val = ft_strdup(current_dir);
		if (!oldpwd->env_val && errno == ENOMEM)
			return (free_n(oldpwd), ft_close(cmds, tree->head, tree), exit(1));
		oldpwd->visible = 0;
		oldpwd->next = NULL;
		ft_lstadd(tree->head, oldpwd);
	}
}

int	changing_current_directory(char **cmds, char *path, t_token_tree *tree)
{
	char		current_dir[PATH_MAX];

	if (chdir(path) == -1)
	{
		if (!getcwd(current_dir, sizeof(current_dir)) && errno != ENOENT)
		{
			chdir("/");
			getcwd(current_dir, sizeof(current_dir));
			update_pwd(cmds, tree, current_dir);
		}
		else if (!search_for_env(tree->head, "PWD"))
		{
			getcwd(current_dir, sizeof(current_dir));
			update_pwd(cmds, tree, current_dir);
		}
		print_err("minishell: cd: ", path, ": ");
		return (print_err(strerror(errno), "\n", NULL), -1);
	}
	if (!getcwd(current_dir, sizeof(current_dir)) && errno == ENOENT)
		return (caseof_long_error(tree, cmds, path), -1);
	else if (!getcwd(current_dir, sizeof(current_dir)) && errno != ENOENT)
		return (print_err(strerror(errno), "\n", NULL), -1);
	if (search_for_env(tree->head, "PWD"))
		update_oldpwd(search_for_env(tree->head, "PWD")->env_val, cmds, tree);
	return (update_pwd(cmds, tree, current_dir), 0);
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

int	open_heredoc_tmp(char **holder, int i, t_env_vars *head)
{
	int		j;
	char	*tmp;

	j = 0;
	while (j < i)
	{
		if (set_token_type(holder[j]) == HEREDOC)
		{
			if (holder[j + 1] && set_token_type(holder[j + 1]) == CMD_T)
			{
				remove_empty_space(holder[j + 1]);
				get_first_cmd(holder[j + 1]);
				tmp = continue_heredoc(ignore_quotes(&holder[j + 1]),
						NULL, holder, 0);
				if (!tmp)
					return (define_exit_status(head, "1"), 0);
				free(tmp);
			}
		}
		j++;
	}
	g_is_heredoc[0] = 0;
	g_is_heredoc[1] = 0;
	return (1);
}
