#include "../parse_header.h"

void    close_all_fds(int stdout_fd, int stdin_fd, int fds[2])
{
    close(fds[1]); //fail
    close(fds[0]); //fail
    close(stdout_fd); //fail
    close(stdin_fd); //fail
}

int execute_left_pipe(t_token_tree *left, int fds[2], int stdout_fd, int stdin_fd)
{
    dup2(fds[1], 1);
    close(fds[0]); //fail
    close(fds[1]); //fail
    close(stdin_fd); //fail
    close(stdout_fd); //fail
    if (execute_tree(left) == -1)
        return (-1);
    exit(0);
}

int execute_right_pipe(t_token_tree *right, int fds[2], int stdout_fd, int stdin_fd)
{
    dup2(fds[0], 0); //fail
    close(fds[1]); //fail
    if (right->id == right->cmd_count)
    {
        dup2(stdout_fd, 1); //fail
        //debugging
        // char *r_buffer = get_next_line(0);
        // printf("r_buffer -> %s\n", r_buffer);
    }
    if (execute_tree(right) == -1)
        return (-1);
    close(fds[0]); //fail
    close(stdin_fd); //fail
    close(stdout_fd); //fail
    exit(0);
}

void    execute_pipe(t_token_tree *left, t_token_tree *right)
{
    pid_t       l_pid;
    pid_t       r_pid;
    int         fds[2];
    int         stdout_fd;
    int         stdin_fd;

    stdout_fd = dup(1);
    stdin_fd = dup(0);
    pipe(fds); //fail
    l_pid = fork(); //fail
    if (!l_pid)
        execute_left_pipe(left, fds, stdout_fd, stdin_fd);
    r_pid = fork(); //fail
    if (r_pid != 0)
    {
        dup2(stdout_fd, 1); //fail
        dup2(stdin_fd, 0); //fail
        close_all_fds(stdout_fd, stdin_fd, fds);
    }
    if (!r_pid)
        execute_right_pipe(right, fds, stdout_fd, stdin_fd);
    wait(NULL);
}
