/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/06 12:13:32 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void swap_nodes_content(t_env_vars *env1, t_env_vars *env2)
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
	int         index;
	int         i;
	t_env_vars  *tmp_head;

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

void    create_sorted_lst(t_env_vars *node, t_env_vars **head)
{
	t_env_vars	*newnode;
	t_env_vars	*prev;

	prev = get_last_node(*head);
	newnode = malloc(sizeof(t_env_vars)); //leaks
	if (!*head)
		*head = newnode;
	if (prev)
		prev->next = newnode;
	newnode->env_name = ft_strdup(node->env_name); //leaks
	newnode->env_val = ft_strdup(node->env_val); //leaks
	newnode->next = NULL;
}

t_env_vars  *display_envs_sorted(t_env_vars *head)
{
	int			matches;
	int			ascii_nbr;
	t_env_vars	*tmp;
	t_env_vars	*s_head;

	tmp = NULL;
	s_head = NULL;
	matches = 0;
	ascii_nbr = 33;
	while (ascii_nbr <= 127)
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->env_name[0] == ascii_nbr)
			{
				create_sorted_lst(tmp, &s_head);
				matches++;
			}
			tmp = tmp->next;
		}
		if (matches > 1)
			sort_matched_envs(s_head, matches, ascii_nbr);
		matches = 0;
		ascii_nbr++;
	}
	return (s_head);
}

void    create_env(t_env_vars *node, t_env_vars *head, char *env)
{
	char	**envs;

	envs = ft_split(env, '='); //leaks
	node->env_name = ft_strdup(envs[0]);
	node->env_val = ft_strdup(envs[1]);
	node->next = NULL;
	free_cmds(envs);
	free(envs);
	envs = NULL;
	ft_lstadd(&head, node);
}

t_env_vars  *create_lst(char **envp)
{
	t_env_vars	*head;
	t_env_vars	*newnode;

	head = malloc(sizeof(t_env_vars)); //leaks
	create_env(head, NULL, *envp);
	newnode = malloc(sizeof(t_env_vars)); //leaks
	newnode->env_name = ft_strdup("?");
	newnode->env_val = ft_strdup("0"); //leaks
	newnode->next = NULL;
	ft_lstadd(&head, newnode);
	envp++;
	while (*envp)
	{
		newnode = malloc(sizeof(t_env_vars)); //leaks
		create_env(newnode, head, *envp);
		envp++;
	}
	return (head);
}

void    export_without_arguments(t_env_vars *p_head)
{
	t_env_vars	*tmp_h;
	t_env_vars	*s_head;

	s_head = display_envs_sorted(p_head);
	tmp_h = s_head;
	while (s_head)
	{
		if (s_head->env_name[0] != '?')
		{
			if (s_head->env_val)
				printf("declare -x %s=\"%s\"\n", s_head->env_name, s_head->env_val);
			else
				printf("declare -x %s\n", s_head->env_name);
		}
		s_head = s_head->next;
	}
	free_envs(&tmp_h);
}

void	add_env_var(char **tokens, int nbr_envs, t_env_vars **head)
{
	char	**cmds;
	char *env_name;
	int		i;
	t_env_vars	*tmp;

	cmds = NULL;
	env_name = NULL;
	i = 1;
	tmp = *head;
	while (tmp->env_name[0] != '?')
		tmp = tmp->next;
	while (i <= nbr_envs)
	{
    	cmds = ft_split_one(tokens[i], '='); //leaks
		if (ft_strchr(cmds[0], '+'))
		{	
			env_name = ft_strtrim(cmds[0], "+"); //leaks
			append_env_var(*head, env_name, cmds[1]);
			free(env_name);
		}
		else if (is_string(cmds[0]))
		{
			search_for_env_var(head, cmds[0]);
			lst_add_element(cmds, head, i);
		}
		else
		{
			free(tmp->env_val);
			tmp->env_val = ft_strdup("1");
			printf("export: `%s' : not a valid identifier\n", tokens[i]);
		}
		free_cmds(cmds);
		free(cmds);
		i++;
	}
}

void    print_env_variable(char **cmds, t_env_vars *head, int i)
{
	char    *env_n;

	while (cmds[i] && ft_strchr(cmds[i], '$'))
	{
		env_n = ft_strtrim(cmds[i], "$");
		while (head && head->env_name && ft_strcmp(head->env_name, env_n))
			head = head->next;
		if (head && head->env_name)
		{    
			printf("%s", head->env_val);
			if (head->next)
				printf(" ");
			else
				printf("\n");
		}
		else
			printf("\n");
		i++;
	}
}
