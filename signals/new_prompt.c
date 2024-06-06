#include "../parse_header.h"

void    handle_new_prompt(int signum)
{
    if (signum == SIGINT)
    {    
       	// struct termios term;

		// tcgetattr(STDOUT_FILENO, &term);

		// term.c_lflag &= ~(ECHO);

		// tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
		
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
		// term.c_lflag |= ISIG;
		// tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
    }
	// if (signum == SIGQUIT)
	// 	printf("SIGQUIT received!\n");
}
