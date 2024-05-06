#include "parse_header.h"

void    cd_command(char *path)
{
    if (!path)
        chdir("~");
    if (chdir(path) != 0)
    {
        write(2, "chdir() failed!!\n", 18);
        return ;
    }
}

void    pwd_command()
{
    char buff[PATH_MAX];

    if (!getcwd(buff, sizeof(buff)))
    {
        write(2, "getcwd() failed!!\n", 19);
        return ;
    }
    else
        printf("%s\n", buff);
}

void    echo_command(char *string)
{
    printf("%s", string);
}

void    export_command(t_pipe_list *new_pipe, int index, t_env_vars **env_vars,
    char *token)
{
    char        **cmds;
    static int  env_i;

    cmds = ft_split(token, '=');
    new_pipe->tokens[index].token = NULL;
    new_pipe->tokens[index].type = ENV_VAR;
    env_vars[env_i]->env_name = ft_strdup(cmds[0]);
    env_vars[env_i]->env_val = ft_strdup(cmds[1]);
    env_i++;
}
