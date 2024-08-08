/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:08 by oait-laa          #+#    #+#             */
/*   Updated: 2024/08/08 11:31:21 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HEADER_H
# define PARSE_HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

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
}			t_t_type;

typedef struct s_env_vars
{
	char				*env_name;
	char				*env_val;
	struct s_env_vars	*next;
	int					visible;
}				t_env_vars;

typedef struct s_tree_vars
{
	char		**envp;
	t_env_vars	**head;
}				t_tree_vars;

typedef struct s_token_vars
{
	int			l;
	int			x;
	int			check;
	char		*cmd_holder;
	t_env_vars	*head;
}			t_token_vars;

typedef struct s_token_array
{
	char		*token;
	t_t_type	type;
}				t_token_array;

typedef struct s_stack
{
	t_token_array	*token;
	int				head;
}				t_stack;

typedef struct s_token_tree
{
	int					id;
	int					cmd_count;
	struct s_token_tree	*tree_head_address;
	char				*token;
	t_t_type			type;
	struct s_token_tree	*left;
	struct s_token_tree	*right;
	char				**envp;
	t_env_vars			**head;
}				t_token_tree;

int	g_is_heredoc[2];

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
void			ft_putchar_fd(char c, int fd);
void			ft_bzero(void *s, size_t n);
void			ft_putstr_fd(char *s, int fd);
int				ft_isalpha_quotes(int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s1);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			**ft_split_qt(char const *s, char c);
char			**ft_split(char const *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(const char *s1, const char *s2);
int				cd_command(char **cmds, char *path, t_token_tree *tree);
t_token_tree	*create_node(char *token, t_t_type type, char **envp,
					t_env_vars **head);
t_token_array	*tokenizer(char **input, t_env_vars *head);
void			*free_alloc(char **bigstr, int l);
int				is_inside_quotes(char const *s, int i);
void			pwd_command(t_token_tree *tree, char **cmds);
void			echo_command(t_token_tree *tree, char **cmds);
int				export_command(char **tokens, t_env_vars **head,
					t_token_tree *tree);
int				is_op(char *input);
int				count_token_len(char *input);
char			*get_token(char **input, int num, char *str);
int				count_cmds(char *input);
int				handle_tokens(char **input, char *input_cpy,
					char **holder, int i);
int				handle_cmd(char **input, char *input_cpy, char **holder, int i);
t_stack			shunting_yard(t_token_array *tokens);
int				count_array(t_token_array *tokens);
t_token_tree	*build_tree(t_stack *stack, char **envp, t_env_vars **head);
int				count_env_vars(char **tokens);
int				unset_command(char **cmds, t_token_tree *tree);
void			env_command(t_token_tree *tree, char **cmds, t_env_vars *head);
char			**ft_split_one(char const *s, char c);
t_t_type		set_token_type(char *token);
void			execute_pipe(t_token_tree *tree);
int				exec_command(t_token_tree *tree, char **cmds, int child);
int				scan_syntax(char **holder, t_env_vars *head);
t_t_type		set_token_type(char *token);
void			free_tree(t_token_tree *root);
char			*wildcard(char **str, int i, char *operator);
int				has_wildcard(char *str);
int				execute_tree(t_token_tree *tree, t_env_vars **head, int child);
int				execute_redirection(t_token_tree *tree);
int				is_string(char *str);
void			export_without_arguments(t_env_vars *head, char **tokens,
					t_token_tree *tree);
int				add_env_var(char **tokens, int nbr_envs,
					t_env_vars **head, t_token_tree *tree);
t_env_vars		*get_last_node(t_env_vars *head);
void			lst_add_element(char **tokens, char **cmds,
					t_token_tree *head);
int				join_strings(char **s1, char *s2);
int				handle_wildcard(char **str, char *operator, t_env_vars *head);
int				free_2d_array(char **array);
int				join_wildcard(char **sep_str, char **str, char *operator);
int				filter_files(struct dirent *dir_content, char **sep_str,
					char *str, char **res);
int				count_heredoc_len(char *input);
char			*continue_heredoc(char *delimiter, t_token_array *token_array,
					char **holder, int *l);
char			*ft_split_first(char *str);
int				has_more_cmds(char *str);
char			*ignore_quotes(char **str);
char			*handle_extra_cmd(t_token_array *token_array, char **holder,
					int *check, int i);
char			*handle_multi_heredoc(t_token_array *token_array,
					char **holder, t_token_vars *vars, int i);
void			*handle_first_heredoc(t_token_array *token_array,
					char **holder, int *l, int i);
char			*set_extra_cmd(t_token_array *token_array, char **holder,
					int i, t_token_vars *vars);
int				fill_heredoc(t_token_array *token_array, char **holder,
					int i, t_token_vars *vars);
int				handle_heredoc(t_token_array *token_array, char **holder,
					int *i, t_token_vars *vars);
void			*handle_other_tokens(t_token_array *token_array, char **holder,
					int *i, t_token_vars *vars);
int				free_token_holder(char **holder, t_token_array *token_array,
					int i);
void			ft_lstadd(t_env_vars **lst, t_env_vars *new);
int				print_echo_content(char **cmds, int i, int new_line);
void			replace_nodes_content(t_env_vars *node1, t_env_vars *node2,
					t_token_tree *tree, char **cmds);
t_env_vars		*create_lst(char **envp);
t_env_vars		*search_for_env(t_env_vars **head, char *env_name);
int				append_env_var(char *env_name, char *to_append, char **cmds,
					t_token_tree *tree);
char			*expand_vars(char *holder, t_env_vars *head);
int				ft_isalpha(int c);
char			**ft_env_split(char const *s, char c);
int				ft_isdigit(int c);
int				is_operand(char *str);
int				non_var_name(char *str, int i);
char			*join_var_with_extras(t_env_vars *head, char **words,
					int i, char *extras);
char			*search_for_var(t_env_vars *head, char *env_name);
char			*get_extras_and_join(t_env_vars *head, char **words, int i);
char			*get_extra_chars(char *holder);
int				has_vars(char *str);
int				has_vars_no_quotes(char *str);
void			*join_all_vars(char **words, char **result);
void			execute_heredoc(t_token_tree *tree);
void			define_signals(void);
int				inside_single_quotes(char *s, int i);
int				tokenize(char **input, char *input_cpy, char **holder);
void			handle_node_failure(t_stack *stack,
					t_token_tree **stack_tree, int tree_offset);
void			check_if_has_file(t_token_array *token_array, char **token,
					t_token_vars *vars, char *tmp);
void			ft_close(char **cmds, t_env_vars **head, t_token_tree *tree);
int				count_2d_array_elements(char **arr);
void			free_envs(t_env_vars **head);
void			free_envs(t_env_vars **head);
int				create_env(t_env_vars *node, t_env_vars *head, char *env);
t_env_vars		*display_envs_sorted(t_env_vars *head, char **tokens,
					t_token_tree *tree);
int				exit_command(char **cmds, int child, t_token_tree *tree);
void			null_terminating(char *str, char c);
int				execute_using_execve(t_token_tree *tree, char **cmds,
					char *path);
int				define_exit_status(t_env_vars *head, char *exit_status);
int				execute_rest(char **cmds, t_token_tree *tree);
int				builtins_rest(t_token_tree *tree, char **cmds,
					t_env_vars **head, int child);
void			free_n(t_env_vars *node);
int				home_case(char **cmds, t_token_tree *tree, t_env_vars *head);
int				oldpwd_case(char **cmds, t_token_tree *tree, t_env_vars *head);
int				check_minus_n(char *echo_flag);
int				delete_env(char *cmd, t_token_tree *tree, char **cmds);
void			print_err(char *string1, char *string2, char *string3);
void			switch_multi_redirections(t_token_array *token_array);
int				check_redirections_extras(char **holder);
char			**ignore_quotes_2d_array(char **strs);
int				is_redirection(t_t_type type);
int				is_redirection_heredoc(char *str);
int				must_reorder(char **holder);
int				reorder_tokens(char ***holder);
void			free_token_array(t_token_array *token_array);
int				count_len(char **holder);
int				handle_builtins_failure(t_token_tree *tree, char **cmds);
int				check_expand(t_token_tree *tree, char **str);
int				count_wildcard(char *str);
void			null_terminating_rev(char *string);
int				has_quotes(char *str, char c);
char			**ft_env_split_no_qt(char const *s, char c);
void			safe_close(int fd, t_token_tree *node);
void			delete_env_head(t_env_vars *tmp, t_env_vars **head);
void			delete_env_inside(t_env_vars *tmp, char *cmd,
					char **cmds, t_token_tree *tree);
char			*file_isdir_case(char **cmds,
					t_token_tree *tree, char *path);
void			handle_fork_failure(t_token_tree *tree);
int				expand_filenames(t_token_tree *tree);
int				execute_redirec_in(t_token_tree *tree);
int				execute_redirec_out(t_token_tree *tree);
int				execute_redirec_append(t_token_tree *tree);
void			safe_dup2(t_token_tree *node, int old_fd, int new_fd);
int				safe_dup(int fd, t_token_tree *node);
void			eof_pressed(t_env_vars **head);
int				exit_execve(int status, t_token_tree *tree, char *path, char **cmds);
void			create_newenv(char **tokens, t_token_tree *tree, char **cmds,
					t_env_vars *new_env);
void			set_address(t_token_tree *root, t_token_tree **address);
int				init_heredoc(char *delimiter, char **input, int *stdin_fd);
void			check_between_quotes(char *str, int *i, int *count, char quote);
int				is_bad_syntax(char **holder, int i);
void			set_redirections(t_token_array *token_array,
					t_token_array **tmp_a_o, t_token_array **tmp_i);
t_token_array	*get_redirection(t_token_array *token_array,
					t_token_array *tmp, t_t_type type, t_t_type type2);
int				get_to_last_token(char **holder);
int				check_for_wildcard(t_token_array *token_array,
					t_env_vars *head);
void			init_token_vars(t_token_vars *vars, t_env_vars *head);
int				changing_current_directory(char **cmds, char *path,
					t_token_tree *tree);
int				syntax_error_check(t_env_vars *head, char *input);
void			syntax_error_message(t_env_vars *head, char *input);
void			readline_allocation_failure(t_env_vars *head);
char			*check_syntax(char *input);
char			*return_type(int dquote, int quote, int parenthesis);
t_stack			handle_stack_failure(t_stack *op_stack,
					t_token_array *tokens, t_stack *cmd_stack);
int				handle_heredoc_expand(t_token_array *token_array,
					char **holder, int has_quote, t_token_vars *vars);
int				ambiguous_redirect_error(char *filename);
int				check_ambiguous_without_quotes(char *old_filename,
					t_token_tree *tree);
void			switch_tabs_to_spaces(char *string);
int				init_wildcard(char **str, int i,
					char **res, char ***sep_str);
int				check_plus_op(char *string);
void			add_element_to_envs(t_token_tree *tree, char **cmds,
					char **tokens);
void			check_existing(t_env_vars *prev, char **cmds, char **tokens,
					t_token_tree *tree);
int				check_exit_argument(char *arg);
int				check_overflow_multiple_arguments(long exit_s,
					char **cmds);
int				check_zeros(char *number);
long			ft_atoi_long(const char *str);
char			**linkedlist_to_2d_array(t_env_vars *head);
int				count_linkedlist_size(t_env_vars *lst);
void			handle_shlvl(t_env_vars **head);
void			check_path_and_create(t_env_vars *head);
void			handle_oldpwd(t_env_vars **head);
void			reset_terminal(struct termios *old_term, t_env_vars **head);
int				handle_bad_wildcard(t_token_array *token_array);
void			update_pwd(char **cmds, t_token_tree *tree, char *to_set);
void			update_oldpwd(char *current_dir, char **cmds,
					t_token_tree *tree);
void			handle_pwd(t_env_vars **head);
void			create_exit_status(t_env_vars **head);
void			caseof_long_error(t_token_tree *tree, char **cmds, char *path);
int				check_space_only(char *token);
char			*ignore_first_last_quotes(char *string);
int				join_extra_with_redi(char **holder, int i);
char			*get_second_cmd(char *holder);
void			swap_redirection_op(t_token_array *tmp_a_o, int i,
					int l, t_token_array *token_array);
t_token_array	*find_redirection_double(t_token_array *token_array,
					int i, int l);
void			swap_redirections(t_token_array *first, t_token_array *second);
char			*split_quotes(char *str, t_token_tree *tree);
int				alloc_str_no_qt(int j, t_token_tree *tree,
					char **tmp, char nxt);
char			*alloc_new_str(char *str, int *i);
void			remove_empty_space(char *str);
int				count_str_len_qt(char *str, int i);
int				if_must_add(int j, char **tmp, char nxt);
void			shlvl_cases(t_env_vars *shlvl, t_env_vars **head);
void			long_error(void);
int				open_heredoc_tmp(char **holder, int i, t_env_vars *head);
void			get_first_cmd(char *holder);
void			switch_tabs_to_spaces_nq(char *str);
void			without_quotes_redire(t_token_tree *tree, char *old_filename);
int				recheck_wilcard(char **tmp, int j, char *w_tmp,
					t_token_tree *tree);
char			**realloc_tokens(char **holder, int n, char *extra);
int				has_redirection_extras(char *str);
char			**remove_from_array(char **words, int i);
void			if_must_split(char ***cmds, int n,
					t_token_tree *tree);
char			*remove_space_last(char *str);
int				has_vars_in_quotes(char *str);
int				get_not_inside_qt(char *str, char c);
int				set_flag(char **cmds, int n);
void			update_underscore_env(char *to_set,
					char **cmds, t_token_tree *tree);
void			create_name_val_env(char **cmds, char **tokens,
					t_token_tree *tree, t_env_vars *new_env);
void			handle_underscore(t_env_vars **head);

#endif