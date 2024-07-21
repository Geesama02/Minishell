/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:11:57 by maglagal          #+#    #+#             */
/*   Updated: 2024/07/21 10:17:31 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void    execute_redirec_in(t_token_tree *tree, int pid)
{
    int fd_file;

    expand_filenames(tree->right);
    fd_file = open(ignore_quotes(&tree->right->token), O_RDONLY, S_IRWXU); //fail
    if (fd_file == -1 && errno == ENOENT)
    {
        print_err("minishell: ", tree->right->token, ": No such file or directory\n");
        ft_close(NULL, tree->head, tree);
        exit(1);
    }
    dup2(fd_file, 0); //fail
    close(fd_file); //fail
    if (tree->left->token[0] != '\0')
        execute_tree(tree->left, tree->head, pid);
    ft_close(NULL, tree->head, tree);
    exit(0);
}

void    execute_redirec_out(t_token_tree *tree, int pid)
{
    int fd_file;
    int stdout_cp;

    expand_filenames(tree->right);
    stdout_cp = dup(1);
    fd_file = open(ignore_quotes(&tree->right->token), O_CREAT | O_RDWR | O_TRUNC, S_IRWXU); //fail
    if (fd_file == -1)
    {
        print_err("open() failed!!\n", NULL, NULL);
        ft_close(NULL, tree->head, tree);
        exit(1);
    }
    dup2(fd_file, 1);
    close(fd_file);
    if (tree->left->token[0] != '\0')
        execute_tree(tree->left, tree->head, pid);
    dup2(stdout_cp, 1);
    close(stdout_cp);
    ft_close(NULL, tree->head, tree);
    exit(0);
}

void    execute_redirec_append(t_token_tree *tree, int pid)
{
    int stdout_cp;
    int fd_file;

    expand_filenames(tree->right);
    stdout_cp = dup(1);
    fd_file = open(ignore_quotes(&tree->right->token), O_CREAT | O_RDWR | O_APPEND, 00700);
    if (fd_file == -1)
    {
        print_err("open() failed!!\n", NULL, NULL);
        ft_close(NULL, tree->head, tree);
        exit(1);
    }
    dup2(fd_file, 1);
    close(fd_file);
    if (tree->left->token[0] != 0)
        execute_tree(tree->left, tree->head, pid);
    dup2(stdout_cp, 1);
    close(stdout_cp);
    ft_close(NULL, tree->head, tree);
    exit(0);
}

