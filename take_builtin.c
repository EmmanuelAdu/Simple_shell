#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * INPUT_BUILTIN - checks for the built in commands
 * @USER_INPUT: the input from the user
 * Return: either 1 or 0
 */
int INPUT_BUILTIN(char **USER_INPUT)
{
	int indx;
	const struct inbuilt_command array[] = {
		{"env", _builtin_env},
		{"exit", _builtin_exit},
		{NULL, NULL}
	};
	if (USER_INPUT == NULL)
	{
		return (0);
	}
	if (USER_INPUT[0] == NULL)
	{
		return (0);
	}
	for (indx = 0; array[indx].id != NULL; indx++)
	{
		if (strcmp(USER_INPUT[0], array[indx].id) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * HANDLE_BUILTIN - this function handles the builtin
 * @USER_INPUT: pointer to the input from user
 * Return: 0 or the builtin index
 */
int HANDLE_BUILTIN(char **USER_INPUT)
{
	int IDX;
	const struct inbuilt_command array[] = {
		{"env", _builtin_env},
		{"exit", _builtin_exit},
		{NULL, NULL}
	};

	if (USER_INPUT == NULL)
	{
		return (0);
	}
	if (USER_INPUT[0] == NULL)
	{
		return (0);
	}
	for (IDX = 0; array[IDX].id != NULL; IDX++)
	{
		if (strcmp(USER_INPUT[0], array[IDX].id) == 0)
		{
			return (array[IDX].ptr_func(USER_INPUT));
		}
	}
	return (0);
}

/**
 * _builtin_env - funcition
 * @toks: toks
 * Return: no of increment
 */
int _builtin_env(__attribute((unused)) char **toks)
{
	int a;

	for (a = 0; __environ[a]; a++)
	{
		write(STDOUT_FILENO, __environ[a],
				strlen(__environ[a]));
		write(STDOUT_FILENO, "\n", strlen("\n"));
	}
	return (a);
}

/**
 * _builtin_exit - exit implementation
 * @toks: pointer
 * Return: 1
 */
int _builtin_exit(char **toks)
{
	if (toks[1] != NULL)
		exit(2);
	else
		return (EXIT_CODE);
}
