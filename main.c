#include "parse_header.h"


t_pipe_list *split_pipe(char *input)
{
    int i = 0;
    t_pipe_list *pipe_list = NULL;
    t_pipe_list *head = NULL;
    char **tokens = ft_split(input, '|');
    t_pipe_list *new_pipe = malloc(sizeof(t_pipe_list));
    new_pipe->id = i;
    new_pipe->tokens = ft_split(*tokens, ' ');
    new_pipe->next = NULL;
    pipe_list = new_pipe;
    head = new_pipe;
    tokens++;
    i++;
    while(*tokens)
    {
        new_pipe->next = malloc(sizeof(t_pipe_list));
        new_pipe = new_pipe->next;
        new_pipe->id = i;
        new_pipe->tokens = ft_split(*tokens, ' ');
        new_pipe->next = NULL;
        tokens++;
        i++;
    }
    i = 0;
    while(pipe_list)
    {
        printf("Pipe: %d\n", pipe_list->id);
        while(pipe_list->tokens[i])
        {
            printf("%s\n", pipe_list->tokens[i]);
            i++;
        }
        pipe_list = pipe_list->next;
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

        if (ft_strcmp(*pipe_list->tokens, "exit") == 0)
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