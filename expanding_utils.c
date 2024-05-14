#include "parse_header.h"

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
