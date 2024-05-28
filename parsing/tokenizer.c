/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:33:49 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/28 17:23:30 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

char *get_token(char **input, int num, char *str)
{
	char *tmp;
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	*input += num;
	return (tmp);
}

t_t_type	set_token_type(char *token)
{
	if (ft_strcmp("&&", token) == 0 || ft_strcmp("||", token) == 0
		|| ft_strcmp("|", token) == 0)
		return (OPERATOR_T);
	if (ft_strcmp(">>", token) == 0)
		return (REDIRECTION_A);
	if (ft_strcmp(">", token) == 0)
		return (REDIRECTION_O);
	if (ft_strcmp("<<", token) == 0)
		return (HEREDOC);
	if (ft_strcmp("<", token) == 0)
		return (REDIRECTION_I);
	if (ft_strcmp("(", token) == 0)
		return (PARETHESIS_O);
	if (ft_strcmp(")", token) == 0)
		return (PARETHESIS_C);
	return (CMD_T);
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
	while (**input != '\0' && (!is_op(*input)
		|| (is_op(*input) && is_inside_quotes(input_cpy, *input - input_cpy))))
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
	int j;

	j = 0;
	while (holder[j] != NULL)
	{
		free(holder[j]);
		j++;
	}
	free(holder);
	while (i-- > 0)
		free(token_array[i].token);
	free(token_array);
	return (0);
}

int	copy_to_array(t_token_array *token_array, char *input, char **holder, int j)
{
	int	i;
	t_token_vars	vars;

	i = 0;
	vars.l = 0;
	vars.x = -1;
	vars.check = 0;
	vars.input = input;
	if (*holder == NULL)
		return (free_token_holder(holder, token_array, i), 0);
	if (scan_syntax(holder, input, j) == 0)
		return (free_token_holder(holder, token_array, i));
	while(holder[i] != NULL)
	{
		if (set_token_type(holder[i]) == HEREDOC)
			handle_heredoc(token_array, holder, &i, &vars);
		else
			handle_other_tokens(token_array, holder, &i, &vars);
	}
	if (vars.x != -1)
		vars.l++;
	token_array[vars.l].token = NULL;
	printf("l ==> %d\n", vars.l);
	free(holder);
	return (1);
}

t_token_array *tokenizer(char *input)
{
	t_token_array *token_array;
	char **holder;
	char *input_cpy;
	int i;

	token_array = malloc(sizeof(t_token_array) * (count_cmds(input) + 1));
	if (!token_array)
		return (free(input), exit(1), NULL);
	holder = malloc(sizeof(char *) * (count_cmds(input) + 1));
	if (!holder)
		return (free(input), free(token_array), exit(1), NULL);
	input_cpy = input;
	i = 0;
	while(*input)
	{
		while (*input == ' ')
			input++;
		if (*input == '\0')
			break;
		if (!handle_tokens(&input, input_cpy, holder, i))
			return (NULL);
		i++;
	}
	holder[i] = NULL;
	if (copy_to_array(token_array, input, holder, i) == 0)
		return (NULL);
	return (token_array);
}
