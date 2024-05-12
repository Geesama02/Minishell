/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/12 16:13:33 by maglagal         ###   ########.fr       */
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

int main()
{
	t_token_array *token_array;
	t_stack postfix_stack;
	t_token_tree *ast_tree;
    while(1)
    {
        char *input = readline("Minishell $> ");
        if (input == NULL)
            break;
        if (input[0] == '\0')
            continue;
		if (check_ending_pipe(input, ft_strlen(input) - 1) == 1)
			continue_pipe(&input);
        add_history(input);
		// int i = 0;
		token_array = tokenizer(input);
		// while(token_array[i].token)
		// {
		// 	printf("token ==> %s | type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
		// 	i++;
		// }
		postfix_stack = shunting_yard(token_array);
		ast_tree = build_tree(&postfix_stack);
		// printf("left -> %s\n", ast_tree->left->token);
		// printf("right -> %s\n", ast_tree->right->token);
		// printf("========= stack =========\n");
		// print_stack(&postfix_stack, postfix_stack.head);
		// printf("======== Tree ========\n");
		executing(ast_tree);
		// print_tree(ast_tree, 0);
    }
    return (0);
}