#include "../parse_header.h"

void    execute_pipe(char **envp, t_token_tree *left, t_token_tree *right)
{
    pid_t       l_pid;
    pid_t       r_pid;
    int         fds[2];
    int         stdout_fd;
    int         stdin_fd;

    stdout_fd = dup(1);
    stdin_fd = dup(0);
    if (pipe(fds) == -1)
        write(2, "pipe() function error!!\n", 25);
    dup2(fds[1], 1); //fail
    l_pid = fork();
    if (l_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork fail
    if (l_pid != 0)
        dup2(stdout_fd, 1); //fail
    if (l_pid == 0)
    {
        close(fds[0]); //close fail
        execute(left, envp);
        close(fds[1]); //close fail
        close(stdout_fd); //fail
        close(stdin_fd); //fail
        exit(0);
    }
    dup2(fds[0], 0); //fail
    r_pid = fork();
    if (r_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork fail
    if (r_pid != 0)
    {    
        dup2(stdin_fd, 0); //fail
        close(fds[0]); //fail
        close(stdin_fd); //fail
        close(stdout_fd); //fail
        close(fds[1]); //fail
    }
    if (r_pid == 0)
    {
        if (right->id == right->cmd_count)
        {
            close(fds[1]); //close fail
            dup2(stdout_fd, 1); //fail
        }
        else
            dup2(fds[1], 1); //fail
        execute(right, envp);
        dup2(stdin_fd, 0); //fail
        close(fds[0]); //close fail
        close(fds[1]); //close fail
        close(stdout_fd); //fail
        close(stdin_fd); //fail
        exit(0);
    }
    wait(NULL);
}
