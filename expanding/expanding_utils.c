/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:06:07 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/28 15:10:13 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	append_env_var(char *env_name, char *to_append, char **cmds,
		t_token_tree *tree)
{
	t_env_vars	*tmp;
	char		*new_env_val;
	char		*prev_envval;

	tmp = search_for_env_var(tree->head, env_name);
	if (tmp)
	{
		prev_envval = tmp->env_val;
		new_env_val = ft_strjoin(prev_envval, to_append);
		if (!new_env_val && errno == ENOMEM)
			return (free(env_name), ft_close(cmds, tree->head, tree),
				exit(1), -1);
		free(prev_envval);
		tmp->env_val = new_env_val;
	}
	return (0);
}

t_env_vars	*search_for_env_var(t_env_vars **head, char *env_name)
{
	t_env_vars	*current;

	if (head)
	{
		current = *head;
		while (current && ft_strcmp(current->env_name, env_name))
			current = current->next;
		if (current)
			return (current);
	}
	return (NULL);
}

void	null_terminating(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	str[i] = '\0';
}

int	is_string(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\''
			|| str[i] == ';' || str[i] == ':' || str[i] == '^'
			|| str[i] == '|' || str[i] == '-' || str[i] == '$'
			|| (str[i] == '+' && str[i + 1] == '+')
			|| str[i] == '/' || str[i] == ']' || str[i] == '['
			|| str[i] == '#' || str[i] == '@' || str[i] == '~'
			|| str[i] == '!' || str[i] == ',' || str[i] == '.'
			|| str[i] == '?' || str[i] == '&' || str[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}

void	ft_lstadd(t_env_vars **lst, t_env_vars *new)
{
	t_env_vars	*current;

	if (*lst == NULL || new == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current && current->next != 0)
		current = current->next;
	current->next = new;
}
