/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/08 10:59:53 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

int len(char **s)
{
    int i = 0;
    while(*s)
    {
        i++;
        s++;
    }
    return (i);

}

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
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

int check_if_or_and(char *input)
{
	int i = 0;
	while (input[i])
	{
		if (input[i] == '&' && input[i + 1] == '&')
			return (1);
		else if (input[i] == '|' && input[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int is_op(char *input)
{
	if (ft_strncmp("&&", input, 2) == 0 || ft_strncmp("||", input, 2) == 0
		|| ft_strncmp(">>", input, 2) == 0 || ft_strncmp("<<", input, 2) == 0
		|| *input == '|' || *input == '(' || *input == ')' || *input == '<'
		|| *input == '>')
		return (1);
	return (0);
}
int	is_inside_quotes(char const *s, int i)
{
	int	inside;

	inside = 0;
	// printf("s ==> %s | i ==> %d\n", s, i);
	while (i >= 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
			inside = !inside;
		i--;
	}
	return (inside);
}

int count_token_len(char *input)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] && (!is_op(input + i) || (is_op(input + i) && is_inside_quotes(input, i))))
	{
		count++;
		i++;
	}
	return (count);
}

char *get_token(char **input, int num, char *str)
{
	char *tmp;
	tmp = ft_strdup(str);
	*input += num;
	// printf("i ==> %d | tmp ==> %s\n" tmp);
	return (tmp);
}

int	precedence_prio(char *token)
{
	if (ft_strcmp(token, "&&") == 0)
		return (1);
	if (ft_strcmp(token, "||") == 0)
		return (2);
	if (ft_strcmp(token, "|") == 0)
		return (3);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		return (4);
	return (0);
}

void	stack_push(t_token_array token, t_stack *stack)
{
	stack->token[stack->head].token = ft_strdup(token.token);
	stack->token[stack->head].type = token.type;
	stack->head++;
	// printf("token inside ==> %s\n", stack->token[stack->head].token);
	// stack->token[stack->head]= token;
	
}

t_token_array	stack_pop(t_stack *stack)
{
	if (stack->head > 0)
		stack->head--;
	return (stack->token[stack->head]);
}

int	count_array(t_token_array *tokens)
{
	int i;

	i = 0;
	while(tokens[i].token)
	{
		i++;
	}
	return (i);
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

t_stack shunting_yard(t_token_array *tokens)
{
	t_stack op_stack;
	t_stack cmd_stack;
	int i;
	// printf("array count ==> %d\n", count_array(tokens));
	op_stack.token = malloc(sizeof(t_token_array) * count_array(tokens));
	cmd_stack.token = malloc(sizeof(t_token_array) * (count_array(tokens) + 1));
	op_stack.head = 0;
	cmd_stack.head = 0;
	i = 0;
	while (tokens[i].token)
	{
		if (tokens[i].type == CMD_T)
			stack_push(tokens[i], &cmd_stack);
		else if (tokens[i].type == OPERATOR_T || tokens[i].type == REDIRECTION_T)
		{
			while (op_stack.head > 0
				&& precedence_prio(op_stack.token[op_stack.head - 1].token) >= precedence_prio(tokens[i].token)
				&& op_stack.token[op_stack.head - 1].type != PARETHESIS_O)
			{
				stack_push(op_stack.token[op_stack.head - 1], &cmd_stack);
				op_stack.head--;
			}

			stack_push(tokens[i], &op_stack);

		}
		else if (tokens[i].type == PARETHESIS_O)
			stack_push(tokens[i], &op_stack);
		else if (tokens[i].type == PARETHESIS_C)
		{
			while (op_stack.head > 0 && op_stack.token[op_stack.head - 1].type != PARETHESIS_O)
			{
				stack_push(op_stack.token[op_stack.head - 1], &cmd_stack);
				op_stack.head--;
			}
			op_stack.head--;
		}
		
		i++;
	}
	while (op_stack.head > 0)
	{
		// printf("op_token ==> %s\n", op_stack.token[op_stack.head - 1].token);
		stack_push(op_stack.token[op_stack.head - 1], &cmd_stack);
		op_stack.head--;
	}
	
	return (cmd_stack);
	
}

int 	count_cmds(char *input)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] && (ft_strncmp("&&", input + i, 2) == 0 || ft_strncmp("||", input + i, 2) == 0
			|| ft_strncmp(">>", input + i, 2) == 0 || ft_strncmp("<<", input + i, 2) == 0))
			i += 2;
		else if (input[i] && (input[i] == '|' || input[i] == '(' || input[i] == ')' || input[i] == '<'
			|| input[i] == '>'))
			i++;
		else {
			
			if (input[i] == ' ')
			{
				i++;
				continue;
			}
			while (input[i] != '\0' && (!is_op(input + i) || (is_op(input + i) && is_inside_quotes(input, i))))
				i++;
		}
		count++;
	}
	return (count);
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

t_t_type	set_token_type(char *token)
{
	if (ft_strcmp("&&", token) == 0 || ft_strcmp("||", token) == 0
		|| ft_strcmp("|", token) == 0)
		return (OPERATOR_T);
	if (ft_strcmp(">>", token) == 0 || ft_strcmp(">", token) == 0
		|| ft_strcmp("<", token) == 0)
		return (REDIRECTION_T);
	if (ft_strcmp("(", token) == 0)
		return (PARETHESIS_O);
	if (ft_strcmp(")", token) == 0)
		return (PARETHESIS_C);
	return (CMD_T);
}

t_token_array *tokenizer(char *input)
{
	t_token_array *token_array = malloc(sizeof(t_token_array) * (count_cmds(input) + 1));
	char **holder = malloc(sizeof(char *) * (count_cmds(input) + 1));
	char *input_cpy = input;
	int i;
	int j;
	i = 0;
	while(*input)
	{
		if (ft_strncmp("&&", input, 2) == 0)
			holder[i] = get_token(&input, 2, "&&");
		else if (ft_strncmp("||", input, 2) == 0)
			holder[i] = get_token(&input, 2, "||");
		else if (ft_strncmp("|", input , 1) == 0)
			holder[i] = get_token(&input, 1, "|");
		else if (ft_strncmp("(", input , 1) == 0)
			holder[i] = get_token(&input, 1, "(");
		else if (ft_strncmp(")", input , 1) == 0)
			holder[i] = get_token(&input, 1, ")");
		else if (ft_strncmp(">", input , 1) == 0)
			holder[i] = get_token(&input, 1, ">");
		else if (ft_strncmp(">>", input , 2) == 0)
			holder[i] = get_token(&input, 2, ">>");
		else if (ft_strncmp("<", input , 1) == 0)
			holder[i] = get_token(&input, 1, "<");
		else if (ft_strncmp("<<", input , 2) == 0)
			holder[i] = get_token(&input, 2, "<<");
		else
		{
			j = 0;
			if (*input == ' ')
			{
				input++;
				continue;
			}
			// printf("len = %d\n", count_token_len(input));
			holder[i] = malloc(count_token_len(input) + 1);
			while (*input != '\0' && (!is_op(input) || (is_op(input) && is_inside_quotes(input_cpy, input - input_cpy))))
			{
				holder[i][j] = *input;
				input++;
				j++;
			}
			holder[i][j] = '\0';
		}
		i++;
	}
	holder[i] = NULL;
	i = 0;
	while(holder[i] != NULL)
	{
		// if (holder[i + 1] && set_token_type(holder[i]) == CMD_T 
		// 		&& set_token_type(holder[i + 1]) == CMD_T)
		token_array[i].token = ft_strdup(holder[i]);
		// while (holder[i + 1] && set_token_type(holder[i]) == CMD_T 
		// 		&& set_token_type(holder[i + 1]) == CMD_T)
		// {
		// 	token_array[i].token = ft_strjoin(holder[i], holder[i + 1]);
		// 	i++;
		// }
		token_array[i].type = set_token_type(holder[i]);
		// printf("token ==> %s | type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
		free(holder[i]);
		// printf("i ==> %d\n", *holder[i]);
		i++;
	}
	token_array[i].token = NULL;
	free(holder);
	// (void)token_array;
	
	return (token_array);
}

t_token_tree	*build_tree(t_stack *stack)
{
	int i;
	// t_stack tmp_stack;
	t_token_tree	**stack_tree;
	t_token_tree	*tmp_right;
	t_token_tree	*tmp_left;
	int	tree_offset;

	stack_tree = malloc(sizeof(t_token_tree *) * stack->head);

	i = 0;
	tree_offset = 0;
	// tmp_stack.token = malloc(sizeof(t_token_array) * stack->head);
	// tmp_stack.head = 0;
	while(stack->token[i].token)
	{
		if (stack->token[i].type == CMD_T)
		{
			stack_tree[tree_offset] = create_node(stack->token[i].token, CMD_T);
			tree_offset++;
		}
		else if ((stack->token[i].type == REDIRECTION_T || stack->token[i].type == OPERATOR_T)
				&& tree_offset > 1)
		{
			tmp_right = stack_tree[tree_offset - 1];
			tmp_left = stack_tree[tree_offset - 2];
			tree_offset -= 2;
			stack_tree[tree_offset] = create_node(stack->token[i].token, stack->token[i].type);
			stack_tree[tree_offset]->right = tmp_right;
			stack_tree[tree_offset]->left = tmp_left;
			tree_offset++;
		}
		i++;
	}

	return (stack_tree[0]);
}

int main()
{
    // t_pipe_list *pipe_list;
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
		int i = 0;
		token_array = tokenizer(input);
		while(token_array[i].token)
		{
			printf("token ==> %s | type ==> %s\n", token_array[i].token, print_type(token_array[i].type));
			i++;
		}
		postfix_stack = shunting_yard(token_array);
		ast_tree = build_tree(&postfix_stack);
		printf("======== Tree ========\n");
		print_tree(ast_tree, 0);
    }
    return (0);
}