#include "parse_header.h"

int executing_command(t_token_tree *tree)
{
    static t_env_vars   *head;
    char                **cmds;

    cmds = ft_split(tree->token, ' ');
    if (!ft_strcmp(cmds[0], "cd"))
    {    
        if (cd_command(cmds[1]) == -1)
            return (-1);
    }
    else if (!ft_strcmp(cmds[0], "pwd"))
    {    
        if (pwd_command(cmds[1]) == -1)
            return (-1);
    }
    else if (!ft_strcmp(cmds[0], "echo"))
    {
        int i;

        i = 1;
        while (cmds[i])
        {
            if (ft_strchr(cmds[i], '$'))
                print_env_variable(cmds[i], head);
            else
            {
                if (echo_command(cmds[i]) == -1)
                    return (-1);
                if (cmds[i + 1])
                {
                    if (echo_command(" ") == -1)
                        return (-1);
                }
            }
            i++;
        }
    }
    else if (!ft_strcmp(cmds[0], "export"))
        head = export_command(cmds, head);
    else if (!ft_strcmp(cmds[0], "unset"))
        unset_command(&head, cmds[1]);
    else if (!ft_strcmp(cmds[0], "env"))
        env_command(cmds[1], head);
    return (0);
}

void    executing(t_token_tree *ex_tree)
{
    if (ex_tree->type == OPERATOR_T && ex_tree->right && ex_tree->left)
    {
        if (ex_tree->left->type == CMD_T
            && ex_tree->right->type == CMD_T)
        {
            if (!ft_strcmp(ex_tree->token, "&&"))
            {
                if (!executing_command(ex_tree->left))
                    executing_command(ex_tree->right);
            }
            else if (!ft_strcmp(ex_tree->token, "||"))
            {
                if (executing_command(ex_tree->left) == -1)
                    executing_command(ex_tree->right);
            }
        }
        else
            executing(ex_tree->left);
    }
    else if (ex_tree->left)
        executing(ex_tree->left);
    else if (ex_tree->right)
        executing(ex_tree->right);
    else if (!ex_tree->left && !ex_tree->right)
        executing_command(ex_tree);
}
