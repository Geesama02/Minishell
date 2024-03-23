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

typedef enum e_token_type
{
    CMD,
    ARG,
    PIPE,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    APPEND_REDIRECTION,
    OUT_FILE,
    IN_FILE,
    APPEND_FILE,
    STR,
    HEREDOC,
    DELIMETER,
} t_token_type;

typedef struct s_token_list
{
    char *token;
    t_token_type type;
} t_token_list;

typedef struct s_pipe_list
{
    int id;
    t_token_list *tokens;
    struct s_pipe_list *next;
} t_pipe_list;


char	**ft_split(char const *s, char c);
int	ft_strcmp(const char *s1, const char *s2);

#endif