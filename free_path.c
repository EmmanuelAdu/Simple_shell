#include <stdio.h>
#include "main.h"
#include <stdlib.h>

/**
 * free_path - this function frees the path
 * @store_path: stores path
 * @store_tokens: store the tokenized ones
 */
void free_path(char **store_path, char **store_tokens)
{
	int i;

	if (store_tokens != NULL)
	{
		for (i = 0; store_tokens[i]; i++)
		{
			if (store_tokens[i] != NULL)
			{
				free(store_tokens[i]);
			}
		}
		free(store_tokens);
	}
	if (*store_path != NULL)
	{
		free(*store_path);
	}
}

/**
 * mem_check - this frees the main function
 * @USER_INPUT: input from user
 * @US_INPUT: pointer to main input
 */
void mem_check(char **USER_INPUT, char *US_INPUT)
{
	int t;

	for (t = 0; USER_INPUT[t]; t++)
	{
		free(USER_INPUT[t]);
	}
	free(USER_INPUT);
	free(US_INPUT);
}

/**
 * second_malloc - second call to malloc
 * @array: the array
 * @size_of_malloc: the size allocated
 * @error_message: message ouput
 * Return: pointer to memory
 */
char **second_malloc(char **array, size_t size_of_malloc, char *error_message)
{
	array = (char **) malloc(sizeof(char *) * size_of_malloc);
	if (array == NULL)
	{
		perror(error_message);
		return (NULL);
	}
	return (array);
}
