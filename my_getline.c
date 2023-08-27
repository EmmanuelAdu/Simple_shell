#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
 * _getline - reads input from the stdin
 * @USER_INPUT: the input from user
 * @INPUT_SIZE: length of input
 * @STATS: status of input
 * Return: the nb of characters read
 */
ssize_t _getline(char **USER_INPUT, size_t *INPUT_SIZE, int STATS)
{
	ssize_t rd_getline;

	rd_getline = getline(USER_INPUT, INPUT_SIZE, stdin);
	if (rd_getline == -1)
	{
		free(*USER_INPUT);
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}
		exit(STATS);
	}
	return (rd_getline);
}
