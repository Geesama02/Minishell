#include "parse_header.h"

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
                if (ft_strcmp(cmds[1], "-n"))
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
        printf("minishell: %s: command not found\n", cmds[0]);
    return (0);
}
