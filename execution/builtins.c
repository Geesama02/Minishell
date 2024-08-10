/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:16 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/09 16:18:28 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	cd_command(char **cmds, char *path, t_token_tree *tree)
{
	if (path && path[0] == '\0')
		return (0);
	if (!path || !ft_strcmp(path, "~"))
	{
		if (home_case(cmds, tree, *tree->head) == -1)
			return (-1);
	}
	else if (!ft_strcmp(path, "-"))
	{
		if (oldpwd_case(cmds, tree, *tree->head) == -1)
			return (-1);
	}
	else
		return (update_underscore_env(NULL, cmds, *tree->head, tree),
			changing_current_directory(cmds, path, tree));
	return (0);
}

void	pwd_command(t_token_tree *tree, char **cmds)
{
	char	*current_dir;
	char	buff[PATH_MAX];

	current_dir = NULL;
	update_underscore_env(NULL, cmds, *tree->head, tree);
	if (search_for_env(tree->head, "PWD"))
	{
		current_dir = search_for_env(tree->head, "PWD")->env_val;
		ft_putstr_fd(current_dir, 1);
		write(1, "\n", 1);
	}
	else
	{
		getcwd(buff, sizeof(buff));
		ft_putstr_fd(buff, 1);
		write(1, "\n", 1);
	}
}

void	echo_command(t_token_tree *tree, char **cmds)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	update_underscore_env(NULL, cmds, *tree->head, tree);
	if (print_echo_content(cmds, i, new_line) == 0)
		return (ft_close(cmds, tree->head, tree), exit(1));
}

int	export_command(char **cmds, t_env_vars **head, t_token_tree *tree)
{
	int	nbr_envs;

	if (!cmds[1])
	{
		update_underscore_env(NULL, cmds, *tree->head, tree);
		export_without_arguments(*head, cmds, tree);
		return (0);
	}
	nbr_envs = count_env_vars(cmds);
	if (add_env_var(cmds, nbr_envs, head, tree) == -1)
		return (-1);
	return (0);
}

int	unset_command(char **cmds, t_token_tree *tree)
{
	int	i;

	i = 1;
	update_underscore_env(NULL, cmds, *tree->head, tree);
	while (cmds[i] && ft_strcmp(cmds[i], "_"))
	{
		if (delete_env(cmds[i], tree, cmds) == -1)
			return (-1);
		i++;
	}
	return (0);
}
