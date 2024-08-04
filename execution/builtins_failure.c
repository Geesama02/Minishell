/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_failure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:32:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 18:19:01 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	print_err(char *string1, char *string2, char *string3)
{
	ft_putstr_fd(string1, 2);
	ft_putstr_fd(string2, 2);
	ft_putstr_fd(string3, 2);
}

int	check_ambiguous_without_quotes(char *old_filename, t_token_tree *tree)
{
	char	**cmds;

	cmds = NULL;
	if (has_quotes(tree->token, '\'') && has_quotes(tree->token, '\"'))
	{
		switch_tabs_to_spaces_nq(tree->token);
		cmds = ft_split(tree->token, ' ');
		if (!cmds)
			return (print_err(strerror(errno), "\n", NULL), ft_close(NULL,
					tree->head, tree), free(old_filename), exit(1), -1);
		if (count_2d_array_elements(cmds) > 1)
			return (free_2d_array(cmds),
				ambiguous_redirect_error(old_filename));
		free_2d_array(cmds);
	}
	return (0);
}

int	ambiguous_redirect_error(char *filename)
{
	print_err("minishell: ", filename, ": ambiguous redirect\n");
	free(filename);
	return (-1);
}
