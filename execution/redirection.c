/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/27 11:25:22 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	expand_filenames(t_token_tree *tree)
{
	char	*old_filename;
	char	**cmds;

	old_filename = ft_strdup(tree->token);
	if (!old_filename)
		return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
				tree->head, tree), free(old_filename), exit(1), -1);
	check_expand(tree);
	if (has_wildcard(tree->token))
		handle_wildcard(&tree->token, "", *tree->head);
	if (tree->token[0] == 0)
		return (print_err("minishell: ", old_filename, ": ambiguous redirect\n"
			), free(old_filename), -1);
	free(old_filename);
	if (has_quotes(tree->token, '\'') && has_quotes(tree->token, '\"'))
	{
		cmds = ft_split(tree->token, ' ');
		if (!cmds)
			return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
					tree->head, tree), exit(1), -1);
		if (count_2d_array_elements(cmds) > 1)
			return (print_err("minishell: ", old_filename,
					": ambiguous redirect\n"), free_2d_array(cmds), -1);
		free_2d_array(cmds);
	}
	return (0);
}

void	execute_redirection_in(t_token_tree *tree)
{
	if (execute_redirec_in(tree) == -1)
		define_exit_status(*tree->head, "1");
}

void	execute_redirection_out(t_token_tree *tree)
{
	if (execute_redirec_out(tree) == -1)
		define_exit_status(*tree->head, "1");
}

void	execute_redirection_append(t_token_tree *tree)
{
	if (execute_redirec_append(tree) == -1)
		define_exit_status(*tree->head, "1");
}

int	execute_redirection(t_token_tree *tree)
{
	if (expand_filenames(tree->right) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	if (tree->type == REDIRECTION_O)
		execute_redirection_out(tree);
	else if (tree->type == REDIRECTION_I)
		execute_redirection_in(tree);
	else if (tree->type == REDIRECTION_A)
		execute_redirection_append(tree);
	return (0);
}
