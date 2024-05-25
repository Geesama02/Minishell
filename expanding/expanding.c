/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/25 18:55:37 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

//debugging (to remove)
void    print_lst(t_env_vars *head)
{
	while (head)
	{
		printf("%s\n", head->env_name);
		head = head->next;
	}
}
//debugging

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
			{
				char *tmpname = tmp_head->next->env_name;
				char *tmpval = tmp_head->next->env_val;
				tmp_head->next->env_name = tmp_head->env_name;
				tmp_head->next->env_val = tmp_head->env_val;
				tmp_head->env_name = tmpname;
				tmp_head->env_val = tmpval;
			}
			tmp_head = tmp_head->next;
			index = 0;
		}
		i++;
	}
}

void    create_sorted_lst(t_env_vars *node, t_env_vars **head)
{
	t_env_vars          *newnode;
	t_env_vars			*prev;

	prev = get_last_node(*head);
	newnode = malloc(sizeof(t_env_vars)); //leaks
	if (!*head)
		*head = newnode;
	if (prev)
		prev->next = newnode;
	newnode->env_name = node->env_name;
	newnode->env_val = node->env_val;
	newnode->next = NULL;
}

t_env_vars  *display_envs_sorted(t_env_vars *head)
{
	int         matches;
	int         ascii_nbr;
	t_env_vars  *tmp;
	t_env_vars  *s_head;
	t_env_vars  *matched_node;

	matches = 0;
	ascii_nbr = 33;
	matched_node = NULL;
	tmp = NULL;
	s_head = NULL;
	while (ascii_nbr <= 127)
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->env_name[0] == ascii_nbr)
			{
				matched_node = tmp;
				create_sorted_lst(matched_node, &s_head);
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
	char    **envs;

	envs = ft_split(env, '='); //leaks
	node->env_name = envs[0];
	node->env_val = envs[1];
	node->next = NULL;
	ft_lstadd(&head, node);
}

t_env_vars  *create_lst(char **envp, t_env_vars *env_head)
{
	t_env_vars *head;
	t_env_vars *newnode;

	head = malloc(sizeof(t_env_vars)); //leaks
	create_env(head, NULL, *envp);
	envp++;
	while (*envp)
	{
		newnode = malloc(sizeof(t_env_vars)); //leaks
		create_env(newnode, head, *envp);
		envp++;
	}
	while (env_head)
	{
		ft_lstadd(&head, env_head);
		env_head = env_head->next;
	}
	return (head);
}

void    export_without_arguments(t_env_vars *p_head, char **envp)
{
	t_env_vars *head;
	t_env_vars *s_head;

	head = create_lst(envp, p_head);
	s_head = display_envs_sorted(head);
	while (s_head)
	{
		if (s_head->env_val)
			printf("declare -x %s=\"%s\"\n", s_head->env_name, s_head->env_val);
		else
			printf("declare -x %s=\"\"\n", s_head->env_name);
		s_head = s_head->next;
	}
}

t_env_vars  *add_env_var(t_env_vars *last_env, char **tokens, int nbr_envs, t_env_vars *head)
{
	int	i;

	i = 1;
	while (i <= nbr_envs)
	{
		if (ft_strchr(tokens[i], '=') || is_string(tokens[i]))
			head = lst_add_element(tokens[i], last_env, head, i);
		else
			printf("export: `%s' : not a valid identifier", tokens[i]);
		i++;
	}
	return (head);
}

void    print_env_variable(char *env_name, t_env_vars *head)
{
	int     i;
	char    *env_n;

	i = 0;
	env_n = ft_strtrim(env_name, "$");
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
}
