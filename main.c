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
        printf("token ==> %s\n", pipe[i]);
        i++;
    }
    i = 0;
    t_pipe_list *new_pipe = malloc(sizeof(t_pipe_list));
    new_pipe->id = i;
    tokens = ft_split(*pipe, ' ');
    new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
    while(tokens[i])
    {
        new_pipe->tokens[i].token = tokens[i];
        printf("token ====> %s\n", new_pipe->tokens[i].token);
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
        new_pipe->tokens = malloc(sizeof(t_token_list) * len(tokens) + 1);
        while (tokens[j])
        {
            new_pipe->tokens[j].token = tokens[j];
            printf("token ====> %s\n", new_pipe->tokens[j].token);
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
            printf("%s\n", pipe_list->tokens[i].token);
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