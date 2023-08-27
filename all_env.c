#include "main.h"

/**
 * create_envar - creating environ variable
 * @v: evironment variable
 * @l: env len
 * @name: name string
 * @val: value string
 */
void create_envar(char **v, unsigned int l, const char *name, const char *val)
{
	*v = check_malloc(v, l, "Error: env_var malloc failed");
	l = strlen(name) + strlen(val) + 2;
	*v = check_malloc(v, l, "Error: env_var malloc failed");
	strcpy(*v, name);
	strcat(*v, "=");
	strcat(*v, val);
	strcat(*v, "\0");
}

/**
 *_unsetenv - function to unset the environment
 *@name: name of environ
 *Return: -1 or 0
 */
int _unsetenv(const char *name)
{
	unsigned int e_i;
	int n_e_i, f_n_i, fnd_i;
	char **new_env;

	new_env = NULL;
	e_i = len_environ();
	fnd_i = _env_name_exists(name);
	if (fnd_i != -1)
	{
		new_env = second_malloc(new_env, e_i, "Error: malloc(unsetenv) failed");
		for (n_e_i = 0; __environ[n_e_i]; n_e_i++)
		{
			if (n_e_i != fnd_i)
				new_env[n_e_i] = malloc(sizeof(char) * strlen(__environ[n_e_i]));
			if (new_env[n_e_i] == NULL)
			{
				perror("Error: malloc(unsetenv failed)");
				for (f_n_i = 0; f_n_i < n_e_i; f_n_i++)
					free(new_env[n_e_i]);
				free(new_env);
				return (-1);

			}
			strcpy(new_env[n_e_i], __environ[n_e_i]);
		}
	}
	new_env[e_i] = NULL;
	__environ = new_env;
	return (0);
}


/**
 * _env_set_exists - short description
 * @v: env var
 * @l: env len
 * @name: name string
 * @overwrite: overwrite integer
 * Return: 0 or -1
 */
int _env_set_exists(char *v, unsigned int l, const char *name, int overwrite)
{
	unsigned int i;

	for (i = 0; __environ[i]; i++)
	{
		if (strncmp(__environ[i], name, strlen(name)) == 0 && overwrite != 0)
		{
			free(__environ[i]);
			__environ[i] = malloc(sizeof(char) * l);
			if (__environ[i] == NULL)
			{
				perror("Error: __environ[env_index] malloc failed");
				free(v);
				return (-1);
			}
			strcpy(__environ[i], v);
			free(v);
			return (0);
		}
	}
	return (0);
}

/**
 * env_does_not_exists - env does not exist
 * @env_var: argument_1 description
 * @envar_length: argument_2 description
 * @env_length: length of enviroment
 * Return: -1 or 0
 */
int env_does_not_exists(char *env_var, unsigned int envar_length,
		unsigned int env_length)
{
	unsigned int free_new_env_index;
	char **new_environ;

	new_environ = (char **) malloc(sizeof(char *) * (env_length + 2));
	if (new_environ == NULL)
	{
		perror("_setenv() Error: new_environ malloc failed");
		free(env_var);
		return (-1);
	}
	copy_array(new_environ, __environ);
	new_environ[env_length] = malloc(sizeof(char) * envar_length);
	if (new_environ[env_length] == NULL)
	{
		perror("_setenv() Error: new_environ[env_index] malloc failed");
		for (free_new_env_index = 0; free_new_env_index < env_length;
				free_new_env_index++)
			free(new_environ[free_new_env_index]);
		free(new_environ);
		free(env_var);
		return (-1);
	}
	strcpy(new_environ[env_length], env_var);
	new_environ[env_length + 1] = NULL;
	free(env_var);
	__environ = new_environ;
	return (0);
}

/**
 * _setenv - set environment
 * @name: name string
 * @value: value string
 * @overwrite: overwrite intger
 * Return: -1 on failure 0 on success
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	unsigned int envar_length;
	char *env_var;

	envar_length = strlen(name) + strlen(value) + 2;
	create_envar(&env_var, envar_length, name, value);
	_env_set_exists(env_var, envar_length, name, overwrite);
	if (_env_name_exists(name) != -1)
		_env_set_exists(env_var, envar_length, name, overwrite);
	else
		env_does_not_exists(env_var, envar_length, len_environ());
	return (0);
}
