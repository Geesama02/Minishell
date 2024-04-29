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

void    export_command(char *string)
{
    char    **cmds;
    int     fd[2];
    char    buffer[64];

    cmds = ft_split(string, '=');
    if (!cmds[1])
    {
        write(2, "you need to specify the varname!!\n", 35);
    }
    else
    {
        pipe(fd);
        write(fd[1], cmds[1], ft_strlen(cmds[1]));
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]);
    }
}
