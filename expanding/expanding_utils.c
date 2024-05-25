#include "../parse_header.h"

void    lst_add_element(char *token, t_env_vars **head, int i)
{
    t_env_vars          *new_env;
    t_env_vars          *prev;
    char                **cmds;

    prev = NULL;
    if (*head)
        prev = get_last_node(*head);
    cmds = ft_split_one(token, '='); //leaks
    new_env = malloc(sizeof(t_env_vars)); //leaks
    if (prev)
        prev->next = new_env;
    else if (!prev && i == 1)
        *head = new_env;
    new_env->env_name = cmds[0];
    if (ft_strchr(token, '='))
        new_env->env_val = cmds[1];
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
            || (str[i] >= 97 && str[i] <= 122))
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
