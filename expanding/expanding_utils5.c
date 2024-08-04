/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:04:57 by maglagal          #+#    #+#             */
/*   Updated: 2024/08/04 11:30:02 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	check_plus_op(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] && i > 0 && string[i] == '+'
			&& string[i + 1] == '\0' && string[i - 1] != '+')
			return (0);
		i++;
	}
	return (-1);
}

void	reset_terminal(struct termios *old_term, t_env_vars **head)
{
	if (tcsetattr(0, TCSANOW, old_term) == -1)
	{
		ft_close(NULL, head, NULL);
		print_err(strerror(errno), "\n", NULL);
		exit(1);
	}
}

int	handle_bad_wildcard(t_token_array *token_array)
{
	if (errno == ENOMEM)
		return (free_token_array(token_array), exit(1), 0);
	return (free_token_array(token_array), 0);
}

void	check_between_quotes_count(char *str, int *i, int *count, char quote)
{
	if (str[*i])
		(*i)++;
	while (str[*i] != quote && str[*i])
	{
		(*i)++;
	}
	(*count)++;
	if (str[*i])
		(*i)++;
}

int	count_quotes_array(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			check_between_quotes_count(str, &i, &count, '\'');
			continue ;
		}
		else if (str[i] == '\"')
		{
			check_between_quotes_count(str, &i, &count, '\"');
			continue ;
		}
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		count++;
	}
	return (count);
}

char	*split_quotes(char *str, t_token_tree *tree)
{
	char	**tmp;
	int i = 0;
	int j = 0;
	char	*result;

	result = ft_strdup("");
	if (!*str)
		return (NULL);
	remove_empty_space(str);
	tmp = malloc(sizeof(char *) * (count_quotes_array(str) + 1));
	if (!tmp)
		return (free(result), NULL);
	while (str[i])
	{
		tmp[j] = alloc_new_str(str, &i);
		if (!alloc_str_no_qt(j, tree, tmp, str[i]))
			return (free(result), free_2d_array(tmp), NULL);
		j++;
	}
	tmp[j] = NULL;
	if (!join_all_vars(tmp, &result))
		return (NULL);
	return (result);
}
