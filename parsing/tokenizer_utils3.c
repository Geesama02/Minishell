/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:03:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/31 16:51:20 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	*handle_other_tokens(t_token_array *token_array, char **holder, int *i, t_token_vars *vars)
{
	if (vars->x != -1)
	{
		vars->l++;
		vars->x = -1;
		vars->check = 0;
	}
	token_array[vars->l].token = ft_strdup(holder[*i]);
	if (!token_array[vars->l].token)
		return (free_token_holder(holder, token_array, vars->l),
			free(vars->input), exit(1), NULL);
	token_array[vars->l].type = set_token_type(holder[*i]);
	free(holder[*i]);
	(*i)++;
	if (has_vars(token_array[vars->l].token))
	{
		token_array[vars->l].token = expand_vars(token_array[vars->l].token, vars->head);
		if (!token_array[vars->l].token)
			return (free_token_holder(holder, token_array, vars->l),
				free(vars->input), exit(1), NULL);
	}
	vars->l++;
	return (NULL);
}
int	inside_single_quotes(char *s, int i)
{
	int quote;

	quote = 0;
	while (i >= 0)
	{
		if (s[i] == '\'')
			quote = !quote;
		i--;
	}
	if (quote)
		return (1);
	return (0);
}

int	has_vars(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == '$' && inside_single_quotes(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

char *search_for_var(t_env_vars *head, char *env_name)
{
	t_env_vars	*tmp;

	tmp = head;
	while (tmp && ft_strcmp(tmp->env_name, env_name) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->env_val);
}

char *get_extra_chars(char *holder)
{
	int	i;

	i = 0;
	while (holder[i])
	{
		if (non_var_name(holder[i]))
			return (holder + i);
		i++;
	}
	return (NULL);
}


char *expand_vars(char *holder, t_env_vars *head)
{
	int	i;
	char **words;
	char *result;
	i = 0;

	result = ft_strdup("");
	if (!result)
		return (free(holder), NULL);
	words = ft_env_split(holder, '$');
	if (!words)
		return (free(holder), free(result), NULL);
	if (*holder != '$')
		i++;
	free(holder);
	while(words[i])
	{
		if (!get_extras_and_join(head, words, i))
			return (free(result), NULL);
		i++;
	}
	if (!join_all_vars(words, &result))
		return (NULL);
	free_2d_array(words);
	return (result);
}
