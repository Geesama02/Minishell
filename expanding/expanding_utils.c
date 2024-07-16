/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:06:07 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 12:31:17 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

int	append_env_var(char *env_name, char *to_append, char **cmds, t_token_tree *tree)
{
	t_env_vars	*tmp;
	char		*new_env_val;

	tmp = *tree->head;
	new_env_val = NULL;
	while (tmp && ft_strcmp(tmp->env_name, env_name))
		tmp = tmp->next;
	if (tmp)
	{
		new_env_val = ft_strjoin(tmp->env_val, to_append); //leaks
		if (!new_env_val && errno == ENOMEM)
			return (free(env_name), ft_close(cmds, tree->head, tree),
				exit(1), -1);
		tmp->env_val = new_env_val;
	}
	return (0);
}

t_env_vars	*search_for_env_var(t_env_vars **head, char *env_name,
		int remove, t_token_tree *tree)
{
	t_env_vars  *current;

	current = *head;
	while (current && ft_strcmp(current->env_name, env_name))
		current = current->next;
	if (current && remove)
	{
		unset_command(head, &current->env_name, tree);
		return (current);
	}
	else if (current && !remove)
		return (current);
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
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90) 
			|| (str[i] >= 97 && str[i] <= 122)
			|| str[i] == 34)
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_lstadd(t_env_vars **lst, t_env_vars *new)
{
	t_env_vars	*current;

	if (!lst || !new)
		return ;
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
