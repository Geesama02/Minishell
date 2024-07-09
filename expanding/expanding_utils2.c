/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:57:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/09 12:20:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

t_env_vars *create_head(char **envp)
{
	t_env_vars	*head;

	head = malloc(sizeof(t_env_vars)); //leaks
	if (!head && errno == ENOMEM)
		return (NULL);
	create_env(head, NULL, *envp);
	return (head);
}

void	create_exit_status(t_env_vars *head)
{
	t_env_vars	*newnode;

	newnode = malloc(sizeof(t_env_vars)); //leaks
	if (!newnode && errno == ENOMEM)
		return (free(head), exit(1));
	newnode->env_name = ft_strdup("?"); //leaks
	if (!newnode->env_name && errno == ENOMEM)
		return (free(head), free(newnode), exit(1));
	newnode->env_val = ft_strdup("0"); //leaks
	if (!newnode->env_val && errno == ENOMEM)
		return (free(head), free(newnode), free(newnode->env_name),
			exit(1));
	newnode->next = NULL;
	ft_lstadd(&head, newnode);
}

t_env_vars  *create_lst(char **envp)
{
	t_env_vars	*head;
	t_env_vars	*newnode;

	head = create_head(envp);
	create_exit_status(head);
	envp++;
	while (*envp)
	{
		newnode = malloc(sizeof(t_env_vars)); //leaks
		if (!newnode && errno == ENOMEM)
			return (free_envs(&head), exit(1), NULL);
		create_env(newnode, head, *envp);
		envp++;
	}
	return (head);
}

int	count_env_vars(char **tokens)
{
	int	counter;

	counter = 0;
	tokens++;
	while (*tokens)
	{
		tokens++;
		counter++;
	}
	return (counter);
}

t_env_vars	*get_last_node(t_env_vars *head)
{
	t_env_vars  *lastnode;

	lastnode = head;
	if (head)
	{
		while (lastnode && lastnode->next)
			lastnode = lastnode->next;
	}
	return (lastnode);
}