#include "../parse_header.h"

void    execute_heredoc(t_token_tree *cmd, t_token_tree *content)
{
    int     fds[2];
    int     stdout_fd;
    int     stdin_fd;
    int     i;

    i = 0;
    stdout_fd = dup(1);
    stdin_fd = dup(0);
    pipe(fds);
    dup2(fds[1], 1);
    dup2(fds[0], 0);
    while (content->token[i])
    {
        write(1, &content->token[i], 1);
        i++;
    }
    dup2(stdout_fd, 1);
    close(stdout_fd);
    close(fds[1]);
    execute_tree(cmd, cmd->head, 1);
    dup2(stdin_fd, 0);
    close(fds[0]);
    close(stdin_fd);
}
