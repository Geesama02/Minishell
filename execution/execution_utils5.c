/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:01:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 18:15:18 by oait-laa         ###   ########.fr       */
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

void	reverse_tokens(t_token_array *token_array, int i, int l, int j)
{
	char	*tmp;
	t_t_type tmp_type;
	char	*tmp2;
	t_t_type tmp2_type;

	while (j < (i - 1 + j) / 2)
	{
		if (is_redirection_heredoc(token_array[j].token)
			&& is_redirection_heredoc(token_array[i - l - 1].token))
		{
			tmp = token_array[j].token;
			tmp_type = token_array[j].type;
			tmp2 = token_array[j + 1].token;
			tmp2_type = token_array[j + 1].type;
			token_array[j].token = token_array[i - l - 1].token;
			token_array[j].type = token_array[i - l - 1].type;
			token_array[j + 1].token = token_array[i - l].token;
			token_array[j + 1].type = token_array[i - l].type;
			token_array[i - l - 1].token = tmp;
			token_array[i - l - 1].type = tmp_type;
			token_array[i - l].token = tmp2;
			token_array[i - l].type = tmp2_type;
		}
		j++;
		l++;
	}
}

int	swap_multi_redirection(t_token_array *token_array, int i, int l)
{
	int		j;

	j = i;
	while (token_array[i].token)
	{
		if (token_array[i].type == OPERATOR_T
			|| token_array[i].type == PARETHESIS_C)
			break;
		i++;
	}
	reverse_tokens(token_array, i, l, j);
	if (token_array[i].token && (token_array[i].type == OPERATOR_T
		|| token_array[i].type == PARETHESIS_C))
	{
		if (token_array[i].type == PARETHESIS_C)
			swap_multi_redirection(token_array, i + 1, 1);
		else
			swap_multi_redirection(token_array, i + 1, 0);
	}
	return (0);
}
