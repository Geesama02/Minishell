#include "../parse_header.h"

void    export_without_arguments(t_env_vars *head, char **envp)
{
    display_envs_sorted(envp);
    while (head)
    {
        if (head->env_val)
            printf("declare -x %s=%s\n", head->env_name, head->env_val);
        else
            printf("declare -x %s\n", head->env_name);
        head = head->next;
    }
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

void    display_envs_sorted(char **envp)
{
    int i;
    int ascii_nbr;

    i = 0;
    ascii_nbr = 0;
    while (ascii_nbr <= 127)
    {
        while (envp[i])
        {
            if (*envp[i] == ascii_nbr)
                printf("declare -x %s\n", envp[i]);
            i++;
        }
        i = 0;
        ascii_nbr++;
    }
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
