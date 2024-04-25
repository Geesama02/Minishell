#include "parse_header.h"

void    cd_command(char *path)
{
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
