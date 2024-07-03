/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:33:49 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/12 10:29:29 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

char	*get_token(char **input, int num, char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	*input += num;
	return (tmp);
}

int	handle_cmd(char **input, char *input_cpy, char **holder, int i)
{
	int	j;

	j = 0;
	if (**input == ' ')
		return (1);
	holder[i] = malloc(count_token_len(*input) + 1);
	if (!holder[i])
		return (free_alloc(holder, i), free(*input), exit(1), 0);
	while (**input != '\0' && (!is_op(*input) || (is_op(*input)
				&& is_inside_quotes(input_cpy, *input - input_cpy))))
	{
		holder[i][j] = **input;
		(*input)++;
		j++;
	}
	holder[i][j] = '\0';
	return (1);
}

int	free_token_holder(char **holder, t_token_array *token_array, int i)
{
	int	j;

	j = 0;
	while (holder[j] != NULL)
	{
		free(holder[j]);
		j++;
	}
	free(holder);
	while (token_array[i].token && i > 0)
	{
		i--;
		free(token_array[i].token);
	}
	if (token_array)
		free(token_array);
	return (0);
}

int	copy_to_array(t_token_array *token_array,
	char **holder, t_env_vars *head)
{
	int				i;
	t_token_vars	vars;

	i = 0;
	vars.l = 0;
	vars.x = -1;
	vars.check = 0;
	vars.head = head;
	if (*holder == NULL)
		return (free_token_holder(holder, token_array, i), 0);
	if (scan_syntax(holder) == 0)
		return (free_token_holder(holder, token_array, i));
	while (holder[i] != NULL)
	{
		if (set_token_type(holder[i]) == HEREDOC)
		{
			if (handle_heredoc(token_array, holder, &i, &vars) == 0)
				return (0);
		}
		else
			handle_other_tokens(token_array, holder, &i, &vars);
	}
	if (vars.x != -1)
		vars.l++;
	token_array[vars.l].token = NULL;
	free_2d_array(holder);
	return (1);
}

t_token_array	*tokenizer(char **input, t_env_vars *head)
{
	t_token_array	*token_array;
	char			**holder;
	char			*input_cpy;

	token_array = malloc(sizeof(t_token_array) * (count_cmds(*input) + 1));
	if (!token_array)
		return (free(*input), exit(1), NULL);
	holder = malloc(sizeof(char *) * (count_cmds(*input) + 1));
	if (!holder)
		return (free(*input), free(token_array), exit(1), NULL);
	input_cpy = *input;
	if (!tokenize(input, input_cpy, holder))
		return (NULL);
	if (copy_to_array(token_array, holder, head) == 0)
		return (NULL);
	return (token_array);
}
