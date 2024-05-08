/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:08 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/08 11:02:36 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HEADER_H
#define PARSE_HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	AND_OPERATOR,
	OR_OPERATOR,
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

typedef enum e_t_type
{
	OPERATOR_T,
	REDIRECTION_T,
	PARETHESIS_O,
	PARETHESIS_C,
	CMD_T
} t_t_type;




typedef struct s_token_array
{
	char *token;
	t_t_type type;
} t_token_array;

typedef struct s_stack
{
	t_token_array *token;
	int head;
} t_stack;

typedef struct s_token_list
{
	char *token;
	t_token_type type;
} t_token_list;

typedef struct s_token_tree
{
	char *token;
	t_t_type type;
	struct s_token_tree *left;
	struct s_token_tree *right;
} t_token_tree;

typedef struct s_pipe_list
{
	int id;
	t_token_list *tokens;
	struct s_pipe_list *next;
} t_pipe_list;


char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
char	*ft_strjoin(char  *s1, char  *s2);
t_token_tree	*fill_token(char *pipe, int i, t_pipe_list *new_pipe);
int		len(char **s);
int		set_type(t_token_list *tokens, char **token, int *i);
int		ft_strlen(char *str);
void	write_error(char *str);
char	*ft_strtrim(char const *s1, char const *set);
int		check_cmd(char *str);
void	cd_command(char *path);
void	pwd_command();
void print_tree(t_token_tree *root, int level);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
t_token_tree *create_node(char *token, t_t_type type);
// char *check_type(t_token_list *tokens);
// t_token_tree *fill_ast(t_token_tree **root, t_token_list *tokens);

#endif