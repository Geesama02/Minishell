/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:42 by oait-laa          #+#    #+#             */
/*   Updated: 2024/04/17 14:51:01 by oait-laa         ###   ########.fr       */
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

void set_type(t_token_list *tokens, char **token, int *i)
{
    if (ft_strcmp(token[*i], "<") == 0)
    {
        tokens[*i].type = INPUT_REDIRECTION;
        if (token[*i + 1])
        {
			tokens[*i + 1].token = token[*i + 1];
            tokens[*i + 1].type = IN_FILE;
            *i += 1;
        }
    }
    else if (ft_strcmp(token[*i], ">") == 0)
    {
        tokens[*i].type = OUTPUT_REDIRECTION;
        if (token[*i + 1])
        {
			tokens[*i + 1].token = token[*i + 1];
            tokens[*i + 1].type = OUT_FILE;
            *i += 1;
        }
    }
    else if (ft_strcmp(token[*i], ">>") == 0)
    {
        tokens[*i].type = APPEND_REDIRECTION;
        if (token[*i + 1])
        {
			tokens[*i + 1].token = token[*i + 1];
            tokens[*i + 1].type = APPEND_FILE;
            *i += 1;
        }
    }
    else if (ft_strcmp(token[*i], "<<") == 0)
    {
        tokens[*i].type = HEREDOC;
        if (token[*i + 1])
        {
			tokens[*i + 1].token = token[*i + 1];
            tokens[*i + 1].type = DELIMETER;
            *i += 1;
        }
    }
    else
        tokens[*i].type = ARG;
}

char *check_type(t_token_list *tokens)
{
    if (tokens->type == CMD)
        return ("CMD");
    else if (tokens->type == ARG)
        return ("ARG");
    else if (tokens->type == PIPE)
        return ("PIPE");
    else if (tokens->type == INPUT_REDIRECTION)
        return ("INPUT_REDIRECTION");
    else if (tokens->type == OUTPUT_REDIRECTION)
        return ("OUTPUT_REDIRECTION");
    else if (tokens->type == APPEND_REDIRECTION)
        return ("APPEND_REDIRECTION");
    else if (tokens->type == OUT_FILE)
        return ("OUT_FILE");
    else if (tokens->type == IN_FILE)
        return ("IN_FILE");
    else if (tokens->type == APPEND_FILE)
        return ("APPEND_FILE");
    else if (tokens->type == STR)
        return ("STR");
    else if (tokens->type == HEREDOC)
        return ("HEREDOC");
    else if (tokens->type == DELIMETER)
        return ("DELIMETER");
    return (NULL);
}

int	check_cmd(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

t_pipe_list *split_pipe(char *input)
{
    int i = 0;
    int j = 0;
    char **tokens;
    t_pipe_list *pipe_list = NULL;
    t_pipe_list *head = NULL;
    printf("input ==> %s\n", input);
    char **pipe = ft_split(input, '|');
    while (pipe[i])
    {
        printf("Pipe token ==> %s\n", pipe[i]);
        i++;
    }
    i = 0;
    t_pipe_list *new_pipe = malloc(sizeof(t_pipe_list));
    new_pipe->id = i;
    tokens = ft_split(*pipe, ' ');
	while(tokens[j])
	{
		printf("B token ==> %s\n", tokens[j]);
		j++;
	}
	j = 0;
    new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
    while(tokens[i])
    {
        new_pipe->tokens[i].token = tokens[i];
        if (i == 0 && check_cmd(tokens[i]) == 1)
            new_pipe->tokens[i].type = CMD;
        else if (i != 0)
            set_type(new_pipe->tokens, tokens, &i);
		else
		{
			write_error("Command not found\n");
			return (NULL);
		}
		printf("P token ==> %s\n", new_pipe->tokens[i].token);
        i++;
    }
    new_pipe->tokens[i].token = NULL;
    i = 0;
    new_pipe->next = NULL;
    pipe_list = new_pipe;
    head = new_pipe;
    pipe++;
    i++;
    while(*pipe)
    {
        new_pipe->next = malloc(sizeof(t_pipe_list));
        new_pipe = new_pipe->next;
        new_pipe->id = i;
        tokens = ft_split(*pipe, ' ');
		while(tokens[j])
		{
			printf("B token ==> %s\n", tokens[j]);
			j++;
		}
		j = 0;
        new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
        while (tokens[j])
        {
            new_pipe->tokens[j].token = tokens[j];
            if (j == 0)
                new_pipe->tokens[j].type = CMD;
            else
                set_type(new_pipe->tokens, tokens, &j);
            j++;
        }
        new_pipe->tokens[j].token = NULL;
        j = 0;
        new_pipe->next = NULL;
        pipe++;
        i++;
    }
    i = 0;
    while(pipe_list)
    {
        printf("Pipe: %d\n", pipe_list->id);
        while(pipe_list->tokens[i].token)
        {
            printf("token ====> %s\n", new_pipe->tokens[i].token);
            printf("type ====> %s\n", check_type(new_pipe->tokens + i));
            printf("========================\n");
            i++;
        }
        pipe_list = pipe_list->next;
        i = 0;
    }

    return (head);
}

int main()
{
    t_pipe_list *pipe_list;
    while(1)
    {
        char *input = readline("Minishell $> ");
        if (input == NULL)
            break;
        if (input[0] == '\0')
            continue;
        add_history(input);
        pipe_list = split_pipe(input);
		if (pipe_list == NULL)
			continue;
        // char **tokens = ft_split(input, '|');
        // char **tokens;

        if (ft_strcmp(pipe_list->tokens->token, "exit") == 0)
        {
            free(input);
            break;
        }
        // while(*tokens)
        // {
        //     printf("%s\n", *tokens);
        //     tokens++;
        // }
    }
    return (0);
}