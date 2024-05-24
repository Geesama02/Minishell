/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:21 by maglagal          #+#    #+#             */
/*   Updated: 2024/05/24 10:32:16 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    display_envs_sorted(t_env_vars *head)
{
    int matches;
    int ascii_nbr;
    t_env_vars *tmp;

    matches = 0;
    ascii_nbr = 0;
    tmp = NULL;
    while (ascii_nbr <= 127)
    {
        tmp = head;
        while (tmp)
        {
            if (*tmp->env_name == ascii_nbr)
                printf("declare -x %s=%s\n", tmp->env_name, tmp->env_val);
            tmp = tmp->next;
            matches++;
        }
        ascii_nbr++;
    }
}

void    create_env(t_env_vars *node, t_env_vars *head, char *env)
{
    char    **envs;

    envs = ft_split(env, '='); //leaks
    node->env_name = envs[0];
    node->env_val = envs[1];
    node->next = NULL;
    ft_lstadd_back(&head, node);
}

t_env_vars  *create_lst(char **envp, t_env_vars *p_head)
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
    while (p_head)
    {
        ft_lstadd_back(&head, p_head);
        p_head = p_head->next;
    }
    return (head);
}

void    export_without_arguments(t_env_vars *p_head, char **envp)
{
    t_env_vars *head = create_lst(envp, p_head);
    display_envs_sorted(head);
    // while (head)
    // {
    //     if (head->env_val)
    //         printf("declare -x %s=%s\n", head->env_name, head->env_val);
    //     else
    //         printf("declare -x %s\n", head->env_name);
    //     head = head->next;
    // }
}

t_env_vars  *add_env_var(t_env_vars *last_env, char **tokens, int nbr_envs, t_env_vars *head)
{
    int         i;

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
