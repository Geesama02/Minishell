/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:01:17 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/11 12:53:59 by maglagal         ###   ########.fr       */
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
