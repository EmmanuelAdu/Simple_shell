#include <stdio.h>
#include "main.h"

/**
 * handle_path - function to handle the path
 * @input: input command
 * Return: value  pointed to by path
 */
char *handle_path(char *input)
{
	int i, path_exist;
	char *store_path, *address_path;
	char **store_tokens;
	struct stat sb;
	char *delim = ":";

	store_path = _getenv("PATH");
	if (store_path != NULL)
	{
		store_tokens = tokenizeAndvalidate(store_path, delim);
		if (store_tokens != NULL)
		{
			for (i = 0; store_tokens[i]; i++)
			{
				create_path(&address_path, store_tokens, input, i);
				path_exist = stat(address_path, &sb);
				if (path_exist == 0)
				{
					free_path(&store_path, store_tokens);
					return (address_path);
				}
				free(address_path);
			}
			free_path(&store_path, store_tokens);
		}
		else
			free(store_path);
	}
	path_exist = stat(input, &sb);
	if (path_exist == 0 && check_valid_path(input))
	{
		return (strdup(input));
	}
	return (NULL);
}

/**
 * _getenv - gets the environment
 * @ptr_env_nm: name of environ
 * Return: pointer to environ
 */
char *_getenv(const char *ptr_env_nm)
{
	char *cp_env;
	char *var_env_name;
	unsigned int indx_env;
	unsigned int len_env;

	for (indx_env = 0; __environ[indx_env]; indx_env++)
	{
		if (strncmp(__environ[indx_env], ptr_env_nm, strlen(ptr_env_nm)) == 0)
		{
			len_env = strlen(__environ[indx_env]) - (strlen(ptr_env_nm));
			var_env_name = malloc(sizeof(char) * len_env);
			if (var_env_name == NULL)
			{
				perror("Error: var_env_name malloc unsuccessful");
				return (NULL);
			}
			cp_env = malloc(sizeof(char) * strlen(__environ[indx_env]) + 1);
			if (cp_env == NULL)
			{
				perror("Error: copying env failed");
				return (NULL);
			}
			strcpy(cp_env, __environ[indx_env]);
			strncpy(var_env_name, cp_env += (strlen(ptr_env_nm) + 1), len_env);
			free(cp_env -= (strlen(ptr_env_nm) + 1));
			return (var_env_name);
		}
	}
	return (NULL);
}

/**
 * create_path - creates the path
 * @address_path: the address of the path
 * @store_tokens: pointer to stored tokens
 * @input: the user command
 * @i: serves as an iterator
 */
void create_path(char **address_path, char **store_tokens,
		char *input, int i)
{
	check_malloc(address_path, (strlen
			(store_tokens[i]) + strlen(input) + 2),
			"Error: filepath failed");
	strcpy(*address_path, store_tokens[i]);
	strcat(*address_path, "/");
	strcat(*address_path, input);
	strcat(*address_path, "\0");
}

/**
 * check_malloc - checks for malloc
 * @address_path: space allocated pointer
 * @entire_len: the total size for allocation
 * @message: the message to printout
 * Return: address of allocated memory
 */
char *check_malloc(char **address_path, size_t entire_len, char *message)
{
	*address_path = (char *) malloc(sizeof(char) * entire_len);
	if (address_path == NULL)
	{
		perror(message);
		return (NULL);
	}
	return (*address_path);
}
