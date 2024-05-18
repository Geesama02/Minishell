#include "parse_header.h"

int cd_command(char *path)
{
    if (!path || (path && !ft_strcmp(path, "~")))
    {
        if (chdir(getenv("HOME")) != 0)
        {
            write(2, "chdir() failed!!\n", 18);
            return (-1);
        }
    }
    else if (chdir(path) != 0)
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
        write(1, buff, ft_strlen(buff));
    return (0);
}

int echo_command(char *string)
{
    if (!string)
    {
        write(1, "\n", 1);
        write(1, "\n", 1);
    }
    while (*string)
    {
        if (write(1, &*string, 1) == -1)
            return (-1);
        string++;
    }
    return (0);
}

t_env_vars  *export_command(char **tokens, t_env_vars *p_head)
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
    head = NULL;
    if (p_head)
    {
        while (p_head->next)
            p_head = p_head->next;
    }
    nbr_envs = count_env_vars(tokens);
    while (i <= nbr_envs)
    {
        if (ft_strchr(tokens[i], '='))
        {
            cmds = ft_split_one(tokens[i], '=');
            env_vars = malloc(sizeof(t_env_vars));
            env_vars->env_name = cmds[0];
            env_vars->env_val = cmds[1];
            if (p_head && i == 1)
            {    
                p_head->next = env_vars;
                head = p_head;
            }
            else if (!p_head && i == 1)
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

void    unset_command(t_env_vars **head, char *cmd)
{
    t_env_vars *tmp;

    tmp = *head;
    if (tmp && !ft_strcmp(tmp->env_name, cmd))
    {    
        tmp->env_name = NULL;
        tmp->env_val = NULL;
        if (tmp->next)
            *head = tmp->next;
        else
            *head = NULL;
        free(tmp);
    }
    else
    {
        while (tmp && tmp->next && ft_strcmp(tmp->next->env_name, cmd))
            tmp = tmp->next;
        if (tmp && tmp->next && tmp->next->next)
            tmp->next = tmp->next->next;
        else
            tmp->next = NULL;
        free(tmp->next);
    }
}

void    env_command(t_env_vars *env_vars, char **envp)
{
    while (*envp)
    {
        while (*envp)
        {    
            printf("%s\n", *envp);
            envp++;
        }
    }
    while (env_vars)
    {
        printf("%s=%s\n", env_vars->env_name, env_vars->env_val);
        env_vars = env_vars->next;
    }
}
