/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/31 16:51:36 by oait-laa         ###   ########.fr       */
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

int check_heredoc(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_strncmp(input + i, "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

char *get_heredoc(char *input)
{
	int i;
	int	j;
	char *delimiter;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_strncmp(input + i, "<<", 2) == 0 && is_inside_quotes(input, i) == 0)
		{
			
			i += 2;
			while (input[i] == ' ')
				i++;
			delimiter = malloc(count_heredoc_len(input + i) + 1);
			while (input[i] && (input[i] != ' ' || (input[i] != ' ' && is_inside_quotes(input, i) == 0))
				&& (!is_op(input + i) || (is_op(input + i) && is_inside_quotes(input, i))))
			{
				delimiter[j] = input[i];
				i++;
				j++;
			}
			delimiter[j] = '\0';
		}
		i++;
	}
	return (delimiter);
}

char	*continue_heredoc(char *delimiter)
{
    char *tmp;
	char *input;
    char *old_input;

	input = ft_strdup("");
    while (1) {
        tmp = readline("> ");
        if (tmp == NULL) // handle ctrl + d here
		{
			if (errno == ENOMEM)
				return (write_error("Allocation Failed"), NULL);
			else
				return (free(tmp), input);
            return (NULL);
		}
        if (tmp[0] == '\0')
		{
            free(tmp);
			old_input = input;
            input = ft_strjoin(old_input, "\n");
            free(old_input);
			continue;
        }
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			return (free(tmp), input);
		}
		old_input = input;
		input = ft_strjoin(old_input, tmp);
		free(old_input);
		free(tmp);
		old_input = input;
		input = ft_strjoin(old_input, "\n");
		free(old_input);
    }
	return (input);
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
	t_token_array	*token_array;
	t_stack			postfix_stack;
	t_token_tree	*ast_tree;
	t_env_vars		*head;

	head = create_lst(envp);
    while(1)
    {
		(void)argc;
		(void)argv;
		(void)envp;
		(void)postfix_stack;
		(void)token_array;
		(void)ast_tree;
        char *input = readline("Minishell$ ");
        if (input == NULL)
			break;
        if (input[0] == '\0')
		{
			free(input);
            continue;
		}
        add_history(input);
		if (check_syntax(input) == 0)
		{
			write_error("Error: parse error\n");
			free(input);
			continue;
		}
		token_array = tokenizer(input, head);
		if (!token_array)
		{
			free(input);
			continue;
		}
		free(input);
		int i = 0;
		while(token_array[i].token)
		{
			printf("token ==> %s -> type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
			i++;
		}
		postfix_stack = shunting_yard(token_array);
		ast_tree = build_tree(&postfix_stack, envp);
		ast_tree->head = head;
		// printf("left -> %s\n", ast_tree->left->token);
		// printf("right -> %s\n", ast_tree->right->token);
		// printf("========= stack =========\n");
		// print_stack(&postfix_stack, postfix_stack.head);
		// printf("======== Tree ========\n");
		// execute_tree(ast_tree, envp);
		print_tree(ast_tree, 0);
		free_tree(ast_tree);
		// wildcard("ft*p*.c");
    }
    return (0);
}