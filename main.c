/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/07/18 16:42:34 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

int	len(char **s)
{
    int i;

	i = 0;
    while (*s)
    {
        i++;
        s++;
    }
    return (i);
}

int check_heredoc(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strncmp(input + i, "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_stack(t_stack *stack, int len)
{
	int	i;

	i = 0;
	printf("=====================\n");
	while (i < len)
	{
		printf("stack_token --> %s\n", stack->token[i].token);
		i++;
	}
	printf("=====================\n");
}

char	*print_type(t_t_type type)
{
	if (type == OPERATOR_T)
		return ("OPERATOR");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == HEREDOC_TOKEN)
		return ("HEREDOC_TOKEN");
	if (type == PARETHESIS_O)
		return ("PARETHESIS_O");
	if (type == PARETHESIS_C)
		return ("PARETHESIS_C");
	if (type == CMD_T)
		return ("CMD_T");
	if (type == REDIRECTION_A)
		return ("REDIRECTION_A");
	if (type == REDIRECTION_I)
		return ("REDIRECTION_I");
	if (type == REDIRECTION_O)
		return ("REDIRECTION_O");
	return ("NULL");
}


void	*free_alloc(char **bigstr, int l)
{
	while (l > 0)
	{
		l--;
		free(bigstr[l]);
	}
	free(bigstr);
	return (NULL);
}

char	*check_syntax(char *input)
{
	int	i;
	int	quote;
	int	dquote;
	int	parenthesis;

	i = 0;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (input[i])
	{
		if (input[i] == ')' && parenthesis == 0 && is_inside_quotes(input, i) == 0)
			return (")");
		if (input[i] == '(' && is_inside_quotes(input, i) == 0)
			parenthesis++;
		if (input[i] == ')' && is_inside_quotes(input, i) == 0)
			parenthesis--;
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	if (dquote)
		return ("\"");
	if (quote)
		return ("\'");
	if (parenthesis)
		return ("(");
	return (NULL);
}

void	a()
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_token_array		*token_array;
	t_stack				postfix_stack;
	t_token_tree		*ast_tree;
	t_env_vars			*head;
	char				*input;

	(void)argc;
	(void)argv;
	is_heredoc[0] = 0;
	is_heredoc[1] = 0;
	rl_catch_signals = 0;
	head = create_lst(envp);
	define_signals();
	// atexit(a);
    while (1)
    {
		// (void)envp;
		// (void)postfix_stack;
		// (void)token_array;
		// (void)ast_tree;
        input = readline("Minishell$ ");
        if (input == NULL)
		{
			if (errno == ENOMEM)
			{
				print_err("readline: allocation failure!\n", NULL, NULL);
				rl_clear_history();
				ft_close(NULL, &head, NULL);
				exit(1);
			}
			else
			{
				rl_clear_history();
				write(0, "exit\n", 5);
				ft_close(NULL, &head, NULL);
				break;
			}
		}
        if (input[0] == '\0')
		{
			// rl_clear_history();
			free(input);
			// ft_close(NULL, &head);
            continue;
		}
        add_history(input);
		if (check_syntax(input))
		{
			print_err("Minishell: syntax error near unexpected token `" , check_syntax(input), "' \n");
			t_env_vars *tmp;
			tmp = head;
			while (tmp->env_name[0] != '?')
				tmp = tmp->next;
			define_exit_status(tmp, "258");
			free(input);
			continue;
		}
		if (is_heredoc[1] == 1)
		{
			t_env_vars *tmp2;
			tmp2 = head;
			tmp2 = search_for_env_var(&head, "?");
			define_exit_status(tmp2, "1");
		}
		token_array = tokenizer(&input, head);
		if (!token_array)
		{
            // printf("out\n");
			// free(input);
			continue;
		}
		// free(input);
		// printf("pid -> %d\n", getpid());
		// int i = 0;
		// while(token_array[i].token)
		// {
		// 	printf("token ==> |%s| -> type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
		// 	i++;
		// }
		postfix_stack = shunting_yard(token_array);
		ast_tree = build_tree(&postfix_stack, envp, &head);
		// printf("left -> %s\n", ast_tree->left->token);
		// printf("right -> %s\n", ast_tree->right->token);
		// printf("========= stack =========\n");
		// print_stack(&postfix_stack, postfix_stack.head);
		// printf("======== Tree ========\n");
		// printf("tree -> %s\n", ast_tree->token);
		// print_tree(ast_tree, 0);
		ast_tree->head = &head;
		execute_tree(ast_tree, ast_tree->head, 1);
		// print_tree(ast_tree, 0);
		free_tree(ast_tree);
		is_heredoc[0] = 0;
		is_heredoc[1] = 0;
    }
    return (0);
}
