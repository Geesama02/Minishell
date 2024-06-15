/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:08 by oait-laa          #+#    #+#             */
/*   Updated: 2024/06/08 16:00:37 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_HEADER_H
# define PARSE_HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h> // to remove just for linux
#include <errno.h>
#include <signal.h>
#include <termios.h>

typedef enum e_t_type
{
	OPERATOR_T,
	REDIRECTION_I,
	REDIRECTION_A,
	REDIRECTION_O,
	HEREDOC,
	HEREDOC_TOKEN,
	PARETHESIS_O,
	PARETHESIS_C,
	CMD_T
} t_t_type;

typedef struct	s_env_vars {
	char *env_name;
	char *env_val;
	struct s_env_vars *next;
}				t_env_vars;

typedef struct	s_tree_vars
{
	char	**envp;
	t_env_vars **head;
	// int	*tree_offset;
} t_tree_vars;

typedef struct s_token_vars
{
	int	l;
	int	x;
	int	check;
	char *input;
	char	*cmd_holder;
	t_env_vars *head;
} t_token_vars;

typedef struct s_token_array
{
	char *token;
	t_t_type type;
} t_token_array;

typedef struct s_stack
{
	t_token_array *token;
	int	head;
} t_stack;


typedef struct s_token_tree
{
	int id;
	int cmd_count;
	char *token;
	t_t_type type;
	struct s_token_tree	*left;
	struct s_token_tree	*right;
	char				**envp;
	t_env_vars			**head;
} t_token_tree;

extern int is_heredoc[2];

void    		ft_putchar(char c);
void    		ft_putstr(char *str);
char			*ft_strdup(const char *s1);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			**ft_split(char const *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(const char *s1, const char *s2);
int				len(char **s);
void			write_error(char *str);
char			*ft_strtrim(char const *s1, char const *set);
int				check_cmd(char *str);
int				cd_command(char *path);
char			*remove__quotes(char *str);
void 			print_tree(t_token_tree *root, int level);
t_token_tree	*create_node(char *token, t_t_type type, char **envp, t_env_vars **head);
t_token_array	*tokenizer(char *input, t_env_vars *head);
void			*free_alloc(char **bigstr, int l);
int				is_inside_quotes(char const *s, int i);
int				pwd_command();
int				echo_command(char **cmds, t_env_vars *head);
void			export_command(char **tokens, t_env_vars **head);
int				is_op(char *input);
int				count_token_len(char *input);
char			*get_token(char **input, int num, char *str);
int 			count_cmds(char *input);
int				handle_tokens(char **input, char *input_cpy, char **holder, int i);
int				handle_cmd(char **input, char *input_cpy, char **holder, int i);
t_stack			shunting_yard(t_token_array *tokens);
int				count_array(t_token_array *tokens);
t_token_tree	*build_tree(t_stack *stack, char **envp, t_env_vars **head);
int				count_env_vars(char **tokens);
void			print_env_variable(char **cmds, t_env_vars *head, int i);
void			unset_command(t_env_vars **head, char *cmd);
void			env_command(t_env_vars *env_vars);
char			**ft_split_one(char const *s, char c);
t_t_type		set_token_type(char *token);
void			execute_pipe(t_token_tree *left, t_token_tree *right);
int				exec_command(char **cmds, char **envp, t_env_vars **head);
int				exec_normal_commands(t_token_tree *tree);
int				scan_syntax(char **holder, char *input);
int				unclosed_var(char *str, char c);
t_t_type		set_token_type(char *token);
void			free_tree(t_token_tree *root);
char			*wildcard(char *str);
int				has_wildcard(char *str);
int				execute_tree(t_token_tree *tree, t_env_vars **head);
void			execute_redirection(t_token_tree *tree);
int				is_string(char *str);
void			export_without_arguments(t_env_vars *head);
void			add_env_var(char **tokens, int nbr_envs, t_env_vars **head);
t_env_vars		*get_last_node(t_env_vars *head);
void			lst_add_element(char **cmds, t_env_vars **head, int i);
int				join_strings(char **s1, char *s2);
int				handle_wildcard(char **str, char *input);
int				free_2d_array(char **array);
int				join_wildcard(char **sep_str, char **str, char *input);
int				filter_files(struct dirent *dir_content, char **sep_str, char *str, char **res);
int				count_heredoc_len(char *input);
char			*continue_heredoc(char *delimiter);
char			*ft_split_first(char *str);
int				has_more_cmds(char *str);
char			*ignore_quotes(char *str);
char			*handle_extra_cmd(t_token_array *token_array, char **holder, int *check, int i);
char			*handle_multi_heredoc(t_token_array *token_array, char *holder, t_token_vars *vars);
void			*handle_first_heredoc(t_token_array *token_array, char **holder, int *l, int i);
char			*set_extra_cmd(t_token_array *token_array, char **holder, int i, t_token_vars *vars);
void			*fill_heredoc(t_token_array *token_array, char **holder, int i, t_token_vars *vars);
void			*handle_heredoc(t_token_array *token_array, char **holder, int *i, t_token_vars *vars);
void			*handle_other_tokens(t_token_array *token_array, char **holder, int *i, t_token_vars *vars);
int				free_token_holder(char **holder, t_token_array *token_array, int i);
void			ft_lstadd(t_env_vars **lst, t_env_vars *new);
void			print_echo_content(char **cmds, int i, int new_line);
void			replace_nodes_content(t_env_vars *node1, t_env_vars *node2);
t_env_vars		*create_lst(char **envp);
t_env_vars		*search_for_env_var(t_env_vars **head, char *env_name);
void			append_env_var(t_env_vars *head, char *env_name, char *to_append);
char			*expand_vars(char *holder, t_env_vars *head);
int				ft_isalpha(int c);
char			**ft_env_split(char const *s, char c);
int				ft_isdigit(int c);
int				is_operand(char *str);
int				non_var_name(char c);
char			*join_var_with_extras(t_env_vars *head, char **words, int i, char *extras);
char			*search_for_var(t_env_vars *head, char *env_name);
char			*get_extras_and_join(t_env_vars *head, char **words, int i);
char			*get_extra_chars(char *holder);
int				has_vars(char *str);
int				has_vars_no_quotes(char *str);
void			*join_all_vars(char **words, char **result);
void			execute_heredoc(t_token_tree *cmd, t_token_tree *content);
void			define_signals();
int				inside_single_quotes(char *s, int i);
int				tokenize(char **input, char *input_cpy, char **holder);
void			handle_node_failure(t_stack *stack, t_token_tree **stack_tree,int tree_offset);
void			check_if_has_file(t_token_array *token_array, char **token, t_token_vars *vars, char *tmp);




// delete later
char *print_type(t_t_type type);

#endif