#include "main.h"

/**
 * handle_sigint - this function handles the signal
 * @signal: the signal to handle
 */
void handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		display();
		fflush(stdout);
	}
}

/**
 * display - this function displays a prompt
 */
void display(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", strlen("$ "));
}
