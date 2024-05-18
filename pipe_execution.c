#include "parse_header.h"

void    execute_pipe(char **envp, t_token_tree *left, t_token_tree *right)
{
    char        *buff;
    char        **cmds;
    pid_t       l_pid;
    pid_t       r_pid;
    int         fds[2];
    int         r_fds[2];
    int         stdout_fd;
    int         stdin_fd;

    stdout_fd = dup(1);
    stdin_fd = dup(0);
    if (pipe(fds) == -1)
        write(2, "pipe() function error!!\n", 25);
    dup2(fds[1], 1);
    l_pid = fork();
    if (l_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork fail
    if (l_pid == 0)
    {
        close(fds[0]);
        cmds = ft_split(left->token, ' ');
        exec_command(cmds, envp);
        close(fds[1]);
        exit(0);
    }
    wait(NULL);
    dup2(fds[0], 0);
    if (pipe(r_fds) == -1)
        write(2, "pipe() function failed!!\n", 26); //pipe fail
    r_pid = fork();
    if (r_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork fail
    if (r_pid == 0)
    {
        close(r_fds[0]);
        dup2(stdout_fd, 1);
        buff = get_next_line(0);
        while (buff)
        {
            printf("in the printing!!\n"); 
            printf("%s\n", buff);
            buff = get_next_line(0);
        }
        printf("passed the printing!!\n"); 
        cmds = ft_split(right->token, ' ');
        exec_command(cmds, envp);
        close(r_fds[1]);
        exit(0);
    }
    dup2(stdin_fd, 0);
    dup2(stdout_fd, 1);
    wait(NULL);
    // close(fds[0]); // close fail
    // close(fds[1]);
    close(r_fds[0]); //close fail
    close(r_fds[1]);
}
