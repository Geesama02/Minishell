#ifndef PARSE_HEADER_H
#define PARSE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token_tree
{
    char *token;
    struct s_token_tree *left;
    struct s_token_tree *right;
} t_token_tree;

typedef struct s_pipe_list
{
    int id;
    char **tokens;
    struct s_pipe_list *next;
} t_pipe_list;


char	**ft_split(char const *s, char c);
int	ft_strcmp(const char *s1, const char *s2);

#endif