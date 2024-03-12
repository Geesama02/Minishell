#include "parse_header.h"

int main()
{
    while(1)
    {
        char *input = readline("prompt> ");
        if (input == NULL)
        {
            break;
        }
        char **tokens = ft_split(input, ' ');
        while(*tokens)
        {
            printf("%s\n", *tokens);
            tokens++;
        }
    }
    return 0;
}