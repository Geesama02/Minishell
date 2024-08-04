/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:11:57 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/03 17:29:10 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	execute_redirec_in(t_token_tree *tree)
{
	int		fd_file;
	int		fd_stdin;
	char	*filename_wq;

	fd_stdin = safe_dup(0, tree);
	filename_wq = ignore_quotes(&tree->right->token);
	if (!filename_wq && errno == ENOMEM)
		return (print_err("malloc failed!!\n", NULL, NULL),
			ft_close(NULL, tree->head, tree), exit(1), -1);
	fd_file = open(filename_wq, O_RDONLY, S_IRWXU);
	if (fd_file == -1)
	{
		safe_close(fd_stdin, tree);
		print_err("minishell: ", filename_wq, ": ");
		print_err(strerror(errno), "\n", NULL);
		return (-1);
	}
	safe_dup2(tree, fd_file, 0);
	safe_close(fd_file, tree);
	if (tree->left->token[0] != '\0')
		execute_tree(tree->left, tree->head, 1);
	safe_dup2(tree, fd_stdin, 0);
	safe_close(fd_stdin, tree);
	return (0);
}

int	execute_redirec_out(t_token_tree *tree)
{
	int		fd_file;
	int		stdout_cp;
	char	*filename_wq;

	stdout_cp = safe_dup(1, tree);
	filename_wq = ignore_quotes(&tree->right->token);
	if (!filename_wq && errno == ENOMEM)
		return (print_err("malloc failed!!\n", NULL, NULL),
			ft_close(NULL, tree->head, tree), exit(1), -1);
	fd_file = open(filename_wq, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd_file == -1)
	{
		safe_close(stdout_cp, tree);
		print_err("minishell: ", filename_wq, ": ");
		print_err(strerror(errno), "\n", NULL);
		return (-1);
	}
	safe_dup2(tree, fd_file, 1);
	safe_close(fd_file, tree);
	if (tree->left->token[0] != '\0')
		execute_tree(tree->left, tree->head, 1);
	safe_dup2(tree, stdout_cp, 1);
	safe_close(stdout_cp, tree);
	return (0);
}

int	execute_redirec_append(t_token_tree *tree)
{
	int		stdout_cp;
	int		fd_file;
	char	*filename_wq;

	stdout_cp = safe_dup(1, tree);
	filename_wq = ignore_quotes(&tree->right->token);
	if (!filename_wq && errno == ENOMEM)
		return (print_err("malloc failed!!\n", NULL, NULL),
			ft_close(NULL, tree->head, tree), exit(1), -1);
	fd_file = open(filename_wq, O_CREAT | O_RDWR | O_APPEND, 00700);
	if (fd_file == -1)
	{
		safe_close(stdout_cp, tree);
		print_err("minishell: ", filename_wq, ": ");
		print_err(strerror(errno), "\n", NULL);
		return (-1);
	}
	safe_dup2(tree, fd_file, 1);
	safe_close(fd_file, tree);
	if (tree->left->token[0] != 0)
		execute_tree(tree->left, tree->head, 1);
	safe_dup2(tree, stdout_cp, 1);
	safe_close(stdout_cp, tree);
	return (0);
}
