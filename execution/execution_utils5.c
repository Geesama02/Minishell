/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:01:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 16:32:32 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	alloc_newstr_re(char *str, char *new_str,
	int index_f, int index_l)
{
	int	i;

	i = 0;
	while (index_f <= index_l)
	{
		new_str[i] = str[index_f];
		i++;
		index_f++;
	}
	return (i);
}

int	redirec_edge_case(t_token_tree *tree, char **cmds)
{
	int	fd;

	if (expand_filenames(tree->left->right) == -1)
		return (define_exit_status(*tree->head, "1"), -1);
	fd = open(ignore_quotes(&tree->left->right->token), O_RDONLY);
	if (fd == -1)
		return (print_err("minishell: ", tree->left->right->token, ": "),
			print_err(strerror(errno), "\n", NULL),
			define_exit_status(*tree->head, "1"), -1);
	else
		safe_close(fd, tree);
	if (execute_redirection(tree, cmds) == -1)
		return (-1);
	return (0);
}

void	reverse_tokens(char **holder, int i, int l, int j)
{
	char	*tmp;
	char	*tmp2;

	while (j < (i - 1 + j) / 2)
	{
		if (is_redirection(set_token_type(holder[j]))
			&& is_redirection(set_token_type(holder[i - l - 1])))
		{
			tmp = holder[j];
			tmp2 = holder[j + 1];
			holder[j] = holder[i - l - 1];
			holder[j + 1] = holder[i - l];
			holder[i - l - 1] = tmp;
			holder[i - l] = tmp2;
		}
		j++;
		l++;
	}
}

int	swap_multi_redirection(char **holder, int i, int l)
{
	int		j;

	j = i;
	while (holder[i])
	{
		if (set_token_type(holder[i]) == OPERATOR_T
			|| set_token_type(holder[i]) == PARETHESIS_C)
			break;
		i++;
	}
	reverse_tokens(holder, i, l, j);
	if (holder[i] && (set_token_type(holder[i]) == OPERATOR_T
		|| set_token_type(holder[i]) == PARETHESIS_C))
	{
		if (set_token_type(holder[i]) == PARETHESIS_C)
			swap_multi_redirection(holder, i + 1, 1);
		else
			swap_multi_redirection(holder, i + 1, 0);
	}
	return (0);
}
