/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:06 by oait-laa          #+#    #+#             */
/*   Updated: 2024/05/08 11:03:00 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_header.h"

// void swap_tospace(char *input)
// {
// 	int i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '\t' || input[i] == '\n')
// 			input[i] = ' ';
// 		i++;
// 	}
// }

// int unclosed_quotes(char *str, char c)
// {
// 	int i = 0;
// 	int count = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 		i++;
// 	}
// 	if (count % 2 == 0)
// 		return (0);
// 	return (1);
// }

// int has_quotes(char *str, char c)
// {
// 	int i = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// char *remove_quotes(char *str)
// {
// 	char *tmp;

// 	if (unclosed_quotes(str, '\"') == 1 || unclosed_quotes(str, '\'') == 1)
// 	{
// 		write_error("Error: quotes not closed\n");
// 		return (NULL);
// 	}
// 	else if (has_quotes(str, '\"') == 0)
// 	{
// 		tmp = ft_strtrim(str, "\"");
// 		free(str);
// 		return (tmp);
// 	}
// 	else if (has_quotes(str, '\'') == 0)
// 	{
// 		tmp = ft_strtrim(str, "\'");
// 		free(str);
// 		return (tmp);
// 	}
// 	return (str);
// }


// t_token_tree *fill_token(char *pipe, int i, t_pipe_list *new_pipe)
// {
// 	int j = 0;
// 	char **tokens;
// 	t_token_tree *tree_list = NULL;
// 	// t_token_tree *curr = NULL;
	

// 	if (i == 0)
// 	{
// 		new_pipe->id = i;
// 		new_pipe->next = NULL;
// 	}
// 	else
// 	{
// 		new_pipe->next = malloc(sizeof(t_pipe_list));
// 		new_pipe = new_pipe->next;
// 		new_pipe->id = i;
// 	}
// 	// printf("pipe ==> %s\n", pipe);
// 	swap_tospace(pipe);
// 	tokens = ft_split(pipe, ' ');
// 	// printf("tokens len ==> %d\n", len(tokens));
// 	new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
// 	while (tokens[j])
// 	{
// 		new_pipe->tokens[j].token = remove_quotes(tokens[j]);
// 		if (!new_pipe->tokens[j].token)
// 			return (0);
// 		// printf("inside token ==> %s\n", new_pipe->tokens[j].token);
// 		if (j == 0 && check_cmd(new_pipe->tokens[j].token) == 1)
// 		{
// 			new_pipe->tokens[j].type = CMD;
// 			if (ft_strcmp(new_pipe->tokens[j].token, "cd")  == 0)
// 				cd_command(remove_quotes(tokens[j + 1]));
// 			if (ft_strcmp(new_pipe->tokens[j].token, "pwd")  == 0)
// 				pwd_command();
// 		}
// 		else if (j != 0)
// 		{
// 			if (set_type(new_pipe->tokens, tokens, &j) == 1)
// 				return (0);
// 		}
// 		else
// 		{
// 			write_error("Command not found\n");
// 			return (0);
// 		}

// 		// t_token_tree *node = create_node(tokens[j], CMD);

//         // if (tree_list == NULL) {
//         //     tree_list = node;
//         //     curr = node;
//         // } else if (ft_strcmp(tokens[j], "&&") == 0) {  
//         //     curr->right = node;
//         //     curr = node;
//         // } else {
//         //     curr->left = node;
//         // }
		
// 		// j++;
		
// 	}
// 	free(tokens);
// 	new_pipe->tokens[j].token = NULL;
// 	new_pipe->next = NULL;
// 	return tree_list;
// }
