/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:01:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 17:44:49 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	alloc_newstr_re(char *str, char *new_str,
	int index_f, int index_l)
{
	int	i;

	i = 0;
	while (str[index_f] && index_f <= index_l)
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

	if (expand_filenames(tree->left->right, cmds) == -1)
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

int count_f_index(char *str)
{
	int	index_f;

	index_f = 0;
	while (str[index_f])
	{
		if (str[index_f] != ' ' && str[index_f] != '\t')
			break ;
		index_f++;
	}
	return (index_f);
}

int	count_l_index(char *str)
{
	int index_l;

	index_l = ft_strlen(str);
	if (index_l > 0)
		index_l--;
	while (str[index_l])
	{
		if (str[index_l] != ' ' && str[index_l] != '\t')
			break ;
		index_l--;
	}
	return (index_l);
}

void	reverse_tokens(char **holder, int i, int l, int j)
{
	char	*tmp;
	char	*tmp2;

	while (j < (i - 1 + j) / 2)
	{
		if (is_redirection_heredoc(holder[j])
			&& is_redirection_heredoc(holder[i - l - 1]))
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
