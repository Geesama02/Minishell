#include "../parse_header.h"

void    execute_redirection_in(t_token_tree *tree)
{
    int fd;
    pid_t pid;

    pid = fork(); //fail
    if (!pid)
    {
        fd = open(tree->right->token, O_EXCL | O_CREAT | O_RDONLY, 00700); //fail
        if (fd == -1)
            fd = open(tree->right->token, O_RDONLY, 0700); //fail
        dup2(fd, 0); //fail
        close(fd); //fail
        execute_tree(tree->left, &tree->head);
        exit(0);
    }
    wait(NULL);
}

void    execute_redirection_out(t_token_tree *tree)
{
    int     fd_file;
    int     i;
    pid_t   pid;

    i = 0;
    fd_file = 0;
    pid = fork(); //fail
    if (pid == -1)
        write(2, "fork() failed!!\n", 17); //fork() fail
    else if (pid == 0)
    {
        fd_file = open(tree->right->token, O_CREAT | O_RDWR | O_TRUNC, 00700); //fail
        if (fd_file == -1)
            write(2, "open() failed!!\n", 17); //open() fail
        dup2(fd_file, 1); //fail
        close(fd_file); //fail
        execute_tree(tree->left, &tree->head);
        exit(0);
    }
    wait(NULL);
}

void    execute_redirection(t_token_tree *tree)
{
    if (tree->type == REDIRECTION_O)
        execute_redirection_out(tree);
    else if (tree->type == REDIRECTION_I)
        execute_redirection_in(tree);
}
