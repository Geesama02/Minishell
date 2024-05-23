/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:01:35 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/22 19:55:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse_header.h"

void	stack_push(t_token_array *token, t_stack *stack)
{
	stack->token[stack->head].token = ft_strdup(token->token);
	stack->token[stack->head].type = token->type;
	free(token->token);
	stack->head++;
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

void	empty_stack(t_stack *op_stack, t_stack *cmd_stack, t_token_array *tokens, int i)
{
	while (op_stack->head > 0
		&& precedence_prio(op_stack->token[op_stack->head - 1].token) >= precedence_prio(tokens[i].token)
		&& op_stack->token[op_stack->head - 1].type != PARETHESIS_O)
	{
		stack_push(&op_stack->token[op_stack->head - 1], cmd_stack);
		op_stack->head--;
	}
}

void	postfix_notation(t_stack *op_stack, t_stack *cmd_stack, t_token_array *tokens, int i)
{
	if (tokens[i].type == CMD_T)
		stack_push(&tokens[i], cmd_stack);
	else if (tokens[i].type == OPERATOR_T || tokens[i].type == REDIRECTION_T)
	{
		empty_stack(op_stack, cmd_stack, tokens, i);
		stack_push(&tokens[i], op_stack);
	}
	else if (tokens[i].type == PARETHESIS_O)
		stack_push(&tokens[i], op_stack);
	else if (tokens[i].type == PARETHESIS_C)
	{
		while (op_stack->head > 0 && op_stack->token[op_stack->head - 1].type != PARETHESIS_O)
		{
			stack_push(&op_stack->token[op_stack->head - 1], cmd_stack);
			op_stack->head--;
		}
		free(op_stack->token[op_stack->head - 1].token);
		free(tokens[i].token);
		op_stack->head--;
	}
}

t_stack shunting_yard(t_token_array *tokens)
{
	t_stack op_stack;
	t_stack cmd_stack;
	int i;
	
	op_stack.token = malloc(sizeof(t_token_array) * count_array(tokens));
	cmd_stack.token = malloc(sizeof(t_token_array) * (count_array(tokens) + 1));
	op_stack.head = 0;
	cmd_stack.head = 0;
	i = 0;
	while (tokens[i].token)
	{
		postfix_notation(&op_stack, &cmd_stack, tokens, i);
		i++;
	}
	while (op_stack.head > 0)
	{
		stack_push(&op_stack.token[op_stack.head - 1], &cmd_stack);
		op_stack.head--;
	}
	free(tokens);
	free(op_stack.token);
	return (cmd_stack);
}