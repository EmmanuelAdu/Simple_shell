#include <stdio.h>
#include "main.h"

/**
 * check_valid_path - checks for the validity of path
 * @input: the input from user command
 * Return: 0 or 1
 */
int check_valid_path(char *input)
{
	size_t q;

	q = strlen(input);

	if (q >= strlen("../"))
	{
		if (strncmp(input, "../", strlen("../")) == 0)
		{
			return (1);
		}
	}
	if (q >= strlen("./"))
	{
		if (strncmp(input, "./", strlen("./")) == 0)
		{
			return (1);
		}
	}
	if (q >= strlen("/"))
	{
		if (strncmp(input, "/", strlen("/")) == 0)
		{
			return (1);
		}
	}
	return (0);
}
