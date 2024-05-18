#include "parse_header.h"

// void    execute_redirection(t_token_tree *node)
// {
//     char    **cmds;
//     int     fds[2];
//     pid_t   pid;
//     int     fd_stdout;
//     int     fd_stdin;

//     cmds = ft_split(node->token, ' ');
//     if (ft_strcmp(cmds[2], ">"))
//     {
//         fd_stdout = dup(1);
//         fd_stdin = dup(0);
//         cmds++;
//         pipe(fds);
//         pid = fork();
//         if (pid == -1)
//             write(2, "fork() failed!!\n", 17); //fork fail
//         dup2(fds[0], 0);
//         dup2(fds[1], 1);
//         exec_command(cmds[0]);
//         else if (pid == 0)
//         {
//             while(read(0, ))
//         }
        
//     }
// }