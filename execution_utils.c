#include "parse_header.h"

char *add_slash(char *string)
{
    int i;
    char *f_string;

    f_string = malloc((sizeof(char) * ft_strlen(string)) + 2); //leaks
    i = 0;
    while (string[i])
    {   
        f_string[i] = string[i];
        i++;
    }
    f_string[i] = '/';
    f_string[i + 1] = '\0';
    return (f_string);
}

char *find_path(char **paths, char *cmd)
{
    int         i;
    char        *path;
    struct stat buffer;

    path = NULL;
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], cmd); //leaks
        if (!stat(path, &buffer))
            return (path);
        else
            i++;
    }
    return (NULL);
}

int execute_rest(char **cmds, char **envp)
{
    int     i;
    char    **paths;
    char    *path;

    i = 0;
    paths = ft_split(getenv("PATH"), ':'); //leaks
    while (paths[i])
    {
        paths[i] = add_slash(paths[i]); //leaks
        i++;
    }
    i = 0;
    path = find_path(paths, cmds[0]); //leaks
    if (path)
    {
        if (execve(path, cmds, envp) == -1)
            return (-1);
    }
    return (0);
}


int exec_command(char **cmds, char **envp)
{
    static t_env_vars   *head;

    if (!ft_strcmp(cmds[0], "cd"))
    {    
        if (cd_command(cmds[1]) == -1)
            return (-1);
    }
    else if (!ft_strcmp(cmds[0], "pwd"))
    {    
        if (pwd_command() == -1)
            return (-1);
    }
    else if (!ft_strcmp(cmds[0], "echo"))
    {
        int i;

        i = 1;
        while (cmds[i])
        {
            if (!ft_strcmp(cmds[1], "-n"))
                i++;
            if (ft_strchr(cmds[i], '$'))
                print_env_variable(cmds[i], head);
            else
            {
                if (echo_command(cmds[i]) == -1)
                    return (-1);
                if (cmds[i + 1])
                {
                    if (echo_command(" ") == -1)
                        return (-1);
                }
                if (ft_strcmp(cmds[1], "-n") && !cmds[i + 1])
                {    
                    if (echo_command("\n") == -1)
                        return (-1);
                }
            }
            i++;
        }
    }
    else if (!ft_strcmp(cmds[0], "export"))
        head = export_command(cmds, head);
    else if (!ft_strcmp(cmds[0], "unset"))
        unset_command(&head, cmds[1]);
    else if (!ft_strcmp(cmds[0], "env"))
        env_command(head, envp);
    else if (!ft_strcmp(cmds[0], "exit"))
        exit(0);
    else
    {     
        if (execute_rest(cmds, envp) == -1)
            return (-1);
    }
    // else
    //     printf("minishell: %s: command not found\n", cmds[0]);
    return (0);
}
