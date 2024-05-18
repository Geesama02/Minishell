#include "parse_header.h"

void    execute_pipe(char **envp, t_token_tree *left, t_token_tree *right)
{
    char        **cmds;
    pid_t       l_pid;
    pid_t       r_pid;
    int         fds[2];
    int         r_fds[2];

    if (pipe(fds) == -1)
        write(2, "pipe() function error!!\n", 25);
    dup2(STDOUT_FILENO, fds[1]);
    l_pid = fork();
    if (l_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork error
    if (l_pid == 0)
    {
        close(fds[0]);
        cmds = ft_split(left->token, ' ');
        exec_command(cmds, envp);
        close(fds[1]);
        exit(0);
    }
    wait(NULL);
    dup2(STDIN_FILENO, fds[0]);
    if (pipe(r_fds) == -1)
        write(2, "pipe() function failed!!\n", 26); //pipe error
    r_pid = fork();
    if (r_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork error
    if (r_pid == 0)
    {
        close(r_fds[0]);
        cmds = ft_split(right->token, ' ');
        exec_command(cmds, envp);
        close(r_fds[1]);
        exit(0);
    }
    dup2(fds[1], STDOUT_FILENO);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]); //close error
    close(fds[1]);
    close(r_fds[0]);
    close(r_fds[1]);
}
