/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:14:02 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/09 14:20:03 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	append_element_to_envs(t_token_tree *tree, char **cmds, char *env_name)
{
	append_env_var(env_name, cmds[1], cmds, tree);
}

void	add_element_to_envs(t_token_tree *tree, char **cmds, char **tokens)
{
	t_env_vars	*prev;
	prev = search_for_env(tree->head, cmds[0]);
	if (prev)
	{
		if (cmds[1])
			check_existing(prev, cmds, tokens, tree);
	}
	else
		lst_add_element(tokens, cmds, tree);
}
