#include "../parse_header.h"

void    handle_new_prompt(int signum)
{
    if (signum == SIGINT)
    {    
        printf("ctrl + c pressed!!\n");
        exit(0);
    }
}
