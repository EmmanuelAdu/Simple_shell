#include "main.h"

/**
 * len_environ - this function returns the length of environ
 * Return: length of environment
 */
int len_environ(void)
{
	unsigned int l;

	for (l = 0; __environ[l]; l++)
		;
	return (l);
}

/**
 * _env_name_exists - name can be found
 * @name: name of the environment
 * Return: the position of the environment
 */
int _env_name_exists(const char *name)
{
	int i, is_found;

	is_found = -1;
	for (i = 0; __environ[i]; i++)
	{
		if (strncmp(__environ[i], name, strlen(name)) == 0)
		{
			is_found = i;
		}
	}
	return (is_found);
}

/**
 * copy_array - this copies an array into another
 * @x: one to copy into or destination
 * @y: source input
 * Return: 0 on success
 */
int copy_array(char **x, char **y)
{
	size_t i; /*used as a loop */
	size_t f; /* freeing the loop */

	for (i = 0; y[i]; i++)
	{
		x[i] = malloc(sizeof(char) * strlen(y[i]));
		if (x[i] == NULL)
		{
			perror("Error: copying array(_SETENV) failed");
			for (f = 0; f < i; f++)
			{
				free(x[i]);
			}
			free(x);
			return (-1);
		}

		strcpy(x[i], y[i]);
	}
	return (0);
}
