/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_protections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:53:19 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/07 09:39:16 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	safe_close(int fd, t_token_tree *node)
{
	if (close(fd) == -1)
	{
		ft_close(NULL, node->head, node);
		print_err("minishell: ", strerror(errno), "\n");
		exit(1);
	}
}

void	safe_dup2(t_token_tree *node, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		ft_close(NULL, node->head, node);
		print_err("minishell: ", strerror(errno), "\n");
		exit(1);
	}
}

int	safe_dup(int fd, t_token_tree *node)
{
	int	fd_cpy;

	fd_cpy = dup(fd);
	if (fd_cpy == -1)
	{
		ft_close(NULL, node->head, node);
		print_err("minishell: ", strerror(errno), "\n");
		exit(1);
	}
	return (fd_cpy);
}

char	**ignore_quotes_2d_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = ignore_quotes(&strs[i]);
		i++;
	}
	return (strs);
}

void	handle_fork_failure(t_token_tree *tree)
{
	print_err("minishell: ", strerror(errno), "\n");
	ft_close(NULL, tree->head, tree->tree_head_address);
	exit(1);
}
