/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:08 by oait-laa          #+#    #+#             */
/*   Updated: 2024/04/29 18:13:11 by maglagal         ###   ########.fr       */
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


int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char  *s1, char  *s2);
int		fill_token(char *pipe, int i, t_pipe_list *new_pipe);
int		len(char **s);
int		set_type(t_token_list *tokens, char **token, int *i);
void	write_error(char *str);
char	*ft_strtrim(char const *s1, char const *set);
int		check_cmd(char *str);
void	cd_command(char *path);
void	pwd_command();
void	echo_command(char *string);
void    export_command(char *string);

#endif