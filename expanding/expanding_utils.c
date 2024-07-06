#include "../parse_header.h"

void    append_env_var(t_env_vars *head, char *env_name, char *to_append)
{
    char    *new_env_val;

    new_env_val = NULL;
    while (head && ft_strcmp(head->env_name, env_name))
        head = head->next;
    if (head)
    {
        new_env_val = ft_strjoin(head->env_val, to_append); //leaks
        head->env_val = new_env_val;
    }
}

t_env_vars	*search_for_env_var(t_env_vars **head, char *env_name, int remove)
{
    t_env_vars *current;

    current = *head;
	while (current && ft_strcmp(current->env_name, env_name))
		current = current->next;
	if (current && remove)
	{
        unset_command(head, current->env_name);
        return (current);
    }
    else if (current && !remove)
        return (current);
	return (NULL);
}

void null_terminating(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '$')
        i++;
    str[i] = '\0';
}

void    lst_add_element(char **cmds, t_env_vars **head, int i)
{
    t_env_vars          *new_env;
    t_env_vars          *prev;

    prev = NULL;
    if (*head)
        prev = get_last_node(*head);
    new_env = malloc(sizeof(t_env_vars)); //leaks
    if (prev)
        prev->next = new_env;
    else if (!prev && i == 1)
        *head = new_env;
    new_env->env_name = ft_strdup(cmds[0]);
    if (ft_strchr(cmds[1], '$'))
        null_terminating(cmds[1]);
    if (cmds[1])
        new_env->env_val = ft_strdup(cmds[1]);
    else
        new_env->env_val = NULL;
    new_env->next = NULL;
}

int is_string(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] >= 65 && str[i] <= 90) 
            || (str[i] >= 97 && str[i] <= 122)
            || (str[i] >= 48 && str[i] <= 57))
            i++;
        else
            return (0);
    }
    return (1);
}

int count_env_vars(char **tokens)
{
    int counter;

    counter = 0;
    tokens++;
    while (*tokens)
    {
        tokens++;
        counter++;
    }
    return (counter);
}

t_env_vars *get_last_node(t_env_vars *head)
{
    t_env_vars *lastnode;

    lastnode = head;
    if (head)
    {
        while (lastnode && lastnode->next)
            lastnode = lastnode->next;
    }
    return (lastnode);
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
