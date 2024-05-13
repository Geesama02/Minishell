#include "parse_header.h"

int cd_command(char *path)
{
    if (!path)
        chdir("~");
    if (chdir(path) != 0)
    {
        write(2, "chdir() failed!!\n", 18);
        return (-1);
    }
    return (0);
}

int pwd_command()
{
    char buff[PATH_MAX];

    if (!getcwd(buff, sizeof(buff)))
    {
        write(2, "getcwd() failed!!\n", 19);
        return (-1);
    }
    else
        printf("%s\n", buff);
    return (0);
}

int echo_command(char *string)
{
    while (*string)
    {
        if (write(1, &*string, 1) == -1)
            return (-1);
        string++;
    }
    return (0);
}

t_env_vars  *export_command(char **tokens)
{
    t_env_vars  *env_vars;
    t_env_vars  *prev;
    t_env_vars  *head;
    int         nbr_envs;
    int         i;
    char        **cmds;

    i = 1;
    env_vars = NULL;
    prev = NULL;
    nbr_envs = count_env_vars(tokens);
    while (i <= nbr_envs)
    {
        if (ft_strchr(tokens[i], '='))
        {
            cmds = ft_split(tokens[i], '=');
            env_vars = malloc(sizeof(t_env_vars));
            env_vars->env_name = cmds[0];
            env_vars->env_val = cmds[1];
            if (i == 1)
                head = env_vars;
            env_vars->next = NULL;
            if (i != 1)
                prev->next = env_vars;
            prev = env_vars;
        }
        else
            printf("export: `%s' : not a valid identifier", tokens[i]);
        i++;
    }
    return (head);
}
