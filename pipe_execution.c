#include "parse_header.h"

int execute_without_fork(t_token_tree *node, char **envp)
{
    char    **cmds;

    cmds = ft_split(node->token, ' ');
    if (exec_command(cmds, envp) == -1)
        return (-1);
    return (0);
}

int execute_pipe_node(t_token_tree *node, char **envp)
{
    if (node->type == OPERATOR_T)
    {
        if (node->left->type == CMD_T && node->right->type == CMD_T)
        {
            if (!ft_strcmp(node->token, "&&"))
            {
                if (!execute_without_fork(node->left, envp))
                    execute_without_fork(node->right, envp);
                else
                    return (-1);
            }
            else if (!ft_strcmp(node->token, "||"))
            {
                if (execute_without_fork(node->left, envp) == -1)
                {
                    if (execute_without_fork(node->right, envp) == -1)
                        return (-1);
                }
            }
            else if (!ft_strcmp(node->token, "|"))
                execute_pipe(envp, node->left, node->right);
        }
        else
            execute_pipe_node(node->left, envp);
    }
    else if (node->left)
        execute_pipe_node(node->left, envp);
    else if (node->right)
        execute_pipe_node(node->right, envp);
    else
    {
        if (execute_without_fork(node, envp) == -1)
            return (-1);
    }
    return (0);
}

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
    if (l_pid == 0)
    {
        close(fds[0]); //close fail
        execute_pipe_node(left, envp);
        close(fds[1]); //close fail
        close(stdout_fd); //fail
        close(stdin_fd); //fail
        exit(0);
    }
    dup2(fds[0], 0); //fail
    r_pid = fork();
    if (r_pid == -1)
        write(2, "fork() failed!!\n", 17); //fork fail
    if (r_pid == 0)
    {
        if (right->id == right->cmd_count)
            dup2(stdout_fd, 1); //fail
        execute_pipe_node(right, envp);
        close(stdout_fd); //fail
        close(stdin_fd); //fail
        close(fds[1]); //close fail
        close(fds[0]); //close fail
        exit(0);
    }
    wait(NULL);
    dup2(stdin_fd, 0); //fail
    dup2(stdout_fd, 1); //fail
    close(fds[0]); //fail
    close(fds[1]); //fail
    close(stdout_fd); //fail
    close(stdin_fd); //fail
}
