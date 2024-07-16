/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:01:23 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/16 12:32:30 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	swap_nodes_content(t_env_vars *env1, t_env_vars *env2)
{
	char	*tmpname;
	char	*tmpval;

	tmpname = env2->env_name;
	tmpval = env2->env_val;
	env2->env_name = env1->env_name;
	env2->env_val = env1->env_val;
	env1->env_name = tmpname;
	env1->env_val = tmpval;
}

void    sort_matched_envs(t_env_vars *head, int nbr_matched, int ascii_nbr)
{
	int			index;
	int			i;
	t_env_vars	*tmp_head;

	i = 0;
	index = 0;
	tmp_head = NULL;
	while (head && head->env_name[0] != ascii_nbr)
		head = head->next;
	while (i < nbr_matched)
	{
		tmp_head = head;
		while (tmp_head && tmp_head->next)
		{
			while (tmp_head->env_name[index] == tmp_head->next->env_name[index])
				index++;
			if (tmp_head->env_name[index] > tmp_head->next->env_name[index])
				swap_nodes_content(tmp_head, tmp_head->next);
			tmp_head = tmp_head->next;
			index = 0;
		}
		i++;
	}
}

void    create_sorted_lst(t_env_vars *node, t_env_vars **head, char **tokens, t_token_tree *tree)
{
	t_env_vars  *newnode;
	t_env_vars  *prev;

	prev = get_last_node(*head);
	newnode = malloc(sizeof(t_env_vars)); //leaks
	if (!newnode)
		return (ft_close(tokens, head, tree), exit(1));
	if (!*head)
		*head = newnode;
	if (prev)
		prev->next = newnode;
	newnode->env_name = ft_strdup(node->env_name); //leaks
	if (!newnode->env_name && errno == ENOMEM)
		return (free(newnode), ft_close(tokens, head, tree), exit(1));
	newnode->env_val = ft_strdup(node->env_val); //leaks
	if (!newnode->env_val && errno == ENOMEM)
		return (free(newnode), free(newnode->env_name),
			ft_close(tokens, head, tree), exit(1));
	newnode->next = NULL;
}

t_env_vars  *display_envs_sorted(t_env_vars *head, char **tokens, t_token_tree *tree)
{
	int			matches;
	int         ascii_nbr;
	t_env_vars  *tmp;
	t_env_vars  *s_head;

	matches = 0;
	ascii_nbr = 33;
	s_head = NULL;
	while (ascii_nbr++ <= 127)
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->env_name[0] == ascii_nbr)
			{
				create_sorted_lst(tmp, &s_head, tokens, tree);
				matches++;
			}
			tmp = tmp->next;
		}
		if (matches > 1)
			sort_matched_envs(s_head, matches, ascii_nbr);
		matches = 0;
	}
	return (s_head);
}

int	create_env(t_env_vars *node, t_env_vars *head, char *env)
{
	char	**envs;

	envs = ft_split_qt(env, '='); //leaks
	if (!envs && errno == ENOMEM)
		return (free(node), -1);
	node->env_name = ft_strdup(envs[0]); //leaks
	if (!node->env_name && errno == ENOMEM)
		return (free_2d_array(envs), free(node), -1);
	node->env_val = ft_strdup(envs[1]); //leaks
	if (!node->env_val && errno == ENOMEM)
		return (free_2d_array(envs), free(node->env_name), free(node), -1);
	node->next = NULL;
	free_2d_array(envs);
	envs = NULL;
	ft_lstadd(&head, node);
	return (0);
}
