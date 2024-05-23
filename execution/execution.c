#include "../parse_header.h"

int exec_normal_commands(t_token_tree *tree)
{
    int                 status;
    pid_t               pid;
    char                **cmds;

    status = 0;
    cmds = ft_split(tree->token, ' '); //leaks
    pid = fork();
    if (pid == -1)
        write(2, "fork() failed!!\n", 17); //fail
    else if (pid == 0)
    {
        if (exec_command(cmds, tree->envp) == -1)
            exit(1);
    }
    wait(&status);
    if (status == 1)
        return (-1);
    return (0);
}

int execute_cmds_with_operators(t_token_tree *tree)
{
    if (!ft_strcmp(tree->token, "&&"))
    {
        if (!execute_tree(tree->left))
            execute_tree(tree->right);
        else
            return (-1);
    }
    else if (!ft_strcmp(tree->token, "||"))
    {
        if (execute_tree(tree->left) == -1)
        {
            if (execute_tree(tree->right) == -1)
                return (-1);
        }
    }
    else if (!ft_strcmp(tree->token, "|"))
        execute_pipe(tree->left, tree->right);
    return (0);
}

int    execute_tree(t_token_tree *tree)
{
    if (tree->type == REDIRECTION_T)
        execute_redirection(tree->left->token, tree->right->token, tree->envp);
    else if (!tree->right && !tree->left)
    {    
        if (exec_normal_commands(tree) == -1)
            return (-1);
    }
    else if (tree->type == OPERATOR_T)
    {
        if (execute_cmds_with_operators(tree) == -1)
            return (-1);
    }
    return (0);
}
