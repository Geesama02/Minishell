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

void    export_command(int j, char **tokens,
    t_env_vars **env_vars, t_pipe_list *new_pipe)
{
    int         env_c;
    int         r_j;
    char        **cmds;
    int         env_i;

    env_c = 0;
    env_i = 0;
    r_j = j;
    while (remove__quotes(tokens[j + 1]))
    {
        if (ft_strchr(remove__quotes(tokens[j + 1]), '='))
        {
            env_c++;
            j++;
        }
        else
            break;
    }
    j = r_j;
    new_pipe->tokens[j].token = "export";
    new_pipe->tokens[j].type = ENV_VAR;
    *env_vars = malloc((sizeof(t_env_vars) * env_c) + 1);
    while (env_c-- > 0)
    {
        cmds = ft_split(tokens[j + 1], '=');
        env_vars[env_i]->env_name = ft_strdup(cmds[0]);
        env_vars[env_i]->env_val = ft_strdup(cmds[1]);
        env_i++;
        j++;
    }
    
}
