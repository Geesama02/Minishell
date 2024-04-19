/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:06 by oait-laa          #+#    #+#             */
/*   Updated: 2024/04/19 17:01:20 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

void swap_tospace(char *input)
{
	int i = 0;

	while (input[i])
	{
		if (input[i] == '\t' || input[i] == '\n')
			input[i] = ' ';
		i++;
	}
}

int fill_token(char *pipe, int i, t_pipe_list *new_pipe)
{
	int j = 0;
	char **tokens;

	if (i == 0)
	{
		new_pipe->id = i;
		new_pipe->next = NULL;
	}
	else
	{
		new_pipe->next = malloc(sizeof(t_pipe_list));
		new_pipe = new_pipe->next;
		new_pipe->id = i;
	
	}
	printf("pipe ==> %s\n", pipe);
	swap_tospace(pipe);
	tokens = ft_split(pipe, ' ');
	printf("tokens len ==> %d\n", len(tokens));
	new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
	while (tokens[j])
	{
		new_pipe->tokens[j].token = tokens[j];
		printf("inside token ==> %s\n", new_pipe->tokens[j].token);
		if (j == 0 && check_cmd(tokens[j]) == 1)
			new_pipe->tokens[j].type = CMD;
		else if (j != 0)
		{
			if (set_type(new_pipe->tokens, tokens, &j) == 1)
				return (0);
		}
		else
		{
			write_error("Command not found\n");
			return (0);
		}
		j++;
	}
	free(tokens);
	new_pipe->tokens[j].token = NULL;
	new_pipe->next = NULL;
	return (1);
}
