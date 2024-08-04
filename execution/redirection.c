/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:05:49 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 18:17:31 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	expand_filenames(t_token_tree *tree)
{
	char	*old_filename;

	old_filename = ft_strdup(tree->token);
	if (!old_filename)
		return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
				tree->head, tree), free(old_filename), exit(1), -1);
	check_expand(tree, &tree->token);
	if (has_wildcard(tree->token))
	{
		if (!handle_wildcard(&tree->token, "", *tree->head) && errno == ENOMEM)
			return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
					tree->head, tree), free(old_filename), exit(1), -1);
	}
	if (tree->token[0] == 0)
		return (ambiguous_redirect_error(old_filename));
	if (check_ambiguous_without_quotes(old_filename, tree) == -1)
		return (-1);
	free(old_filename);
	return (0);
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

int	execute_redirection(t_token_tree *tree)
{
	if (expand_filenames(tree->right) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	if (tree->type == REDIRECTION_O)
	{
		if (execute_redirection_out(tree) == -1)
			return (-1);
	}
	else if (tree->type == REDIRECTION_I)
	{
		if (execute_redirection_in(tree) == -1)
			return (-1);
	}
	else if (tree->type == REDIRECTION_A)
	{
		if (execute_redirection_append(tree) == -1)
			return (-1);
	}
	return (0);
}
