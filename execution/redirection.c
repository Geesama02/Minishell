/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 12:13:07 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	expand_filenames(t_token_tree *tree)
{
	char	*old_filename;

	remove_empty_space(tree->token);
	old_filename = ft_strdup(tree->token);
	if (!old_filename)
		return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
				tree->head, tree), free(old_filename), exit(1), -1);
	if (tree->token[0] != '\"')
	{
		check_expand(tree, &tree->token);
		if (has_wildcard(tree->token))
		{
			without_quotes_wildcard(tree, old_filename);
			remove_empty_space(tree->token);
		}
		tree->token = remove_space_first_last(tree->token);
		if (tree->token[0] == 0)
			return (ambiguous_redirect_error(old_filename), -1);
		if (check_ambiguous_without_quotes(old_filename, tree) == -1)
			return (-1);
	}
	else
		check_expand(tree, &tree->token);
	return (free(old_filename), 0);
}

int	execute_redirection_in(t_token_tree *tree)
{
	if (execute_redirec_in(tree) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	return (0);
}

int	execute_redirection_out(t_token_tree *tree)
{
	if (execute_redirec_out(tree) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	return (0);
}

int	execute_redirection_append(t_token_tree *tree)
{
	if (execute_redirec_append(tree) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	return (0);
}

int	execute_redirection(t_token_tree *tree, char **cmds)
{
	static int	failure;

	update_underscore_env(tree->left->token, cmds, *tree->head, tree);
	if (expand_filenames(tree->right) == -1)
		return (failure = 1, define_exit_status(*tree->head, "1"), -1);
	if (tree->type == REDIRECTION_O)
	{
		if (execute_redirection_out(tree) == -1 || failure)
			return (failure = 1, -1);
	}
	else if (tree->type == REDIRECTION_I)
	{
		if (execute_redirection_in(tree) == -1 || failure)
			return (failure = 1, -1);
	}
	else if (tree->type == REDIRECTION_A)
	{
		if (execute_redirection_append(tree) == -1 || failure)
			return (failure = 1, -1);
	}
	return (0);
}
