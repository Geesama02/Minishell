/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:57:37 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/22 15:34:00 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	null_terminating_rev(char *string)
{
	int	len;

	len = ft_strlen(string);
	while (len >= 0 && string[len - 1] == ' ')
	{
		string[len - 1] = '\0';
		len--;
	}
}

void	lst_add_element(char **tokens, char **cmds, t_token_tree *tree,
	int i)
{
	t_env_vars	*new_env;
	t_env_vars	*prev;

	if (*tree->head)
		prev = get_last_node(*tree->head);
	new_env = malloc(sizeof(t_env_vars));
	if (!new_env && errno == ENOMEM)
		return (ft_close(tokens, tree->head, tree),
			free_2d_array(cmds), exit(1));
	if (prev)
		prev->next = new_env;
	else if (!prev && i == 1)
		*tree->head = new_env;
	create_newenv(tokens, tree->head, cmds, new_env);
}
