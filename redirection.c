#include "parse_header.h"

void    execute_redirection(char *cmd, char *file_name, char **envp)
{
    int     fd_file;
    pid_t   pid;
    int     fd_stdout;
    int     i;
    char    **cmds;

    fd_file = 0;
    fd_stdout = dup(1);
    i = 0;
    pid = fork();
    if (pid == -1)
        write(2, "fork() failed!!\n", 17); //fork() fail
    else if (pid == 0)
    {
        fd_file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 00700);
        if (fd_file == -1)
            write(2, "open() failed!!\n", 17); //open() fail
        dup2(fd_file, 1);
        cmds = ft_split(cmd, ' ');
        exec_command(cmds, envp);
        close(fd_file);
        exit(0);
    }
    wait(NULL);
    dup2(fd_stdout, 1);
    close(fd_stdout);
}
