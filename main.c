/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/19 10:12:51 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parse_header.h"

int len(char **s)
{
    int i = 0;
    while (*s)
    {
        i++;
        s++;
    }
    return (i);

}

void write_error(char *str)
{
	write(2, str, ft_strlen(str));
}

int check_ending_pipe(char *input, int len)
{
	while (len > 0)
	{
		if (input[len] == '|')
			return (1);
		else if (input[len] == ' ')
			len--;
		else
			return (0);
	}
	return (0);
}

int continue_pipe(char **input)
{
    char *tmp;
    char *old_input;

    while (1) {
        tmp = readline("Pipe>");
        if (tmp == NULL)
            return (0);
        if (tmp[0] == '\0')
		{
            free(tmp);
            old_input = *input;
            *input = ft_strjoin(old_input, "\n");
            free(old_input);
			continue;
        }
		else if (ft_strcmp(tmp, "exit") == 0)
		{
            free(tmp);
			free(*input);
            return (0);
        }
		else
		{
            old_input = *input;
            *input = ft_strjoin(old_input, tmp);
            free(old_input);
            return (1);
        }
    }
}



void print_stack(t_stack *stack, int len)
{
	int i;

	i = 0;
	printf("=====================\n");
	while (i < len)
	{
		printf("stack_token --> %s\n", stack->token[i].token);
		i++;
	}
	printf("=====================\n");
}

char *print_type(t_t_type type)
{
	if (type == OPERATOR_T)
		return ("OPERATOR");
	if (type == REDIRECTION_T)
		return ("REDIRECTION_T");
	if (type == PARETHESIS_O)
		return ("PARETHESIS_O");
	if (type == PARETHESIS_C)
		return ("PARETHESIS_C");
	if (type == CMD_T)
		return ("CMD_T");
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

int check_syntax(char *input)
{
	int i;
	int quote;
	int dquote;
	int parenthesis;

	i = 0;
	quote = 0;
	dquote = 0;
	parenthesis = 0;
	while (input[i])
	{
		if (input[i] == ')' && parenthesis != 1 && is_inside_quotes(input, i) == 0)
			return (0);
		if (input[i] == '(' && is_inside_quotes(input, i) == 0)
			parenthesis = !parenthesis;
		if (input[i] == ')' && is_inside_quotes(input, i) == 0)
			parenthesis = !parenthesis;
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	if (dquote || quote || parenthesis)
		return (0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_token_array *token_array;
	t_stack postfix_stack;
	t_token_tree *ast_tree;

    while(1)
    {
		(void)argc;
		(void)argv;
		// (void)envp;
        char *input = readline("Minishell $> ");
        if (input == NULL)
			break;
        if (input[0] == '\0')
            continue;
        add_history(input);
		if (check_syntax(input) == 0)
		{
			write_error("Error: parse error\n");
			free(input);
			continue;
		}
		token_array = tokenizer(input);
		if (!token_array)
		{
			write_error("Error: parse error\n");
			free(input);
			continue;
		}
		free(input);
		// while(token_array[i].token)
		// {
		// 	printf("token ==> %s | type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
		// 	i++;
		// }
		(void)postfix_stack;
		(void)ast_tree;
		postfix_stack = shunting_yard(token_array);
		ast_tree = build_tree(&postfix_stack);
		// printf("left -> %s\n", ast_tree->left->token);
		// printf("right -> %s\n", ast_tree->right->token);
		// printf("========= stack =========\n");
		// print_stack(&postfix_stack, postfix_stack.head);
		// printf("======== Tree ========\n");
		execute_tree(ast_tree, envp);
		// print_tree(ast_tree, 0);
		free_tree(ast_tree);
		// wildcard("ft*p*.c");
    }
    return (0);
}