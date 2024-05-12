#include "parse_header.h"

void    print_env_variable(char *env_name, t_env_vars *head)
{
    int     i;
    char    *env_n;

    i = 0;
    env_n = ft_strtrim(env_name, "$");
    while (head && ft_strcmp(head->env_name, env_n))
        head = head->next;
    if (head)
        printf("%s\n", head->env_val);
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
