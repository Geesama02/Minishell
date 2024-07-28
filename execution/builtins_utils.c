/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:33:42 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/28 16:06:47 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	delete_env(char *cmd, t_token_tree *tree, char **cmds)
{
	t_env_vars	*tmp;

	tmp = *tree->head;
	if (!ft_isalpha_quotes(cmd[0]) || !is_string(cmd))
		return (print_err("minishell: unset: `", cmd,
				"': is not a valid identifier\n"), -1);
	else if (tmp && !ft_strcmp(tmp->env_name, cmd))
		delete_env_head(tmp, tree->head);
	else
		delete_env_inside(tmp, cmd, cmds, tree);
	return (0);
}

int	print_echo_content(char **cmds, int i, int new_line)
{
	int	tobe_printed;

	tobe_printed = 0;
	new_line = 1;
	while (cmds[i])
	{
		while (!tobe_printed && cmds[i] && cmds[i][0] == '-'
			&& !check_minus_n(cmds[i]))
		{
			new_line = 0;
			i++;
		}
		if (cmds[i])
		{
			tobe_printed = 1;
			ft_putstr_fd(cmds[i], 1);
			if (cmds[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (1);
}

void	replace_nodes_content(t_env_vars *node1, t_env_vars *node2,
		t_token_tree *tree, char **cmds)
{
	free(node1->env_name);
	free(node1->env_val);
	node1->env_name = ft_strdup(node2->env_name);
	if (!node1->env_name && errno == ENOMEM)
		return (ft_close(cmds, tree->head, tree), exit(1));
	node1->env_val = ft_strdup(node2->env_val);
	if (!node1->env_val && errno == ENOMEM)
		return (free(node1->env_name),
			ft_close(cmds, tree->head, tree), exit(1));
	node1->next = node2->next;
	free(node2->env_name);
	free(node2->env_val);
	free(node2);
}
