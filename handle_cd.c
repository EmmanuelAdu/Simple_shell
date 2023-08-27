#include "main.h"

/**
 * builtin_cd - this function implements the builtin commands
 * @args: pointer to the command
 */
void builtin_cd(char **args)
{
	char *dir, *current_dir, *new_dir;

	if (args[1] == NULL)
		dir = getenv("HOME");
	else if (strcmp(args[1], "-") == 0)
		dir = getenv("OLDPWD");
	else
		dir = args[1];
	current_dir = getcwd(NULL, 0);
	if (current_dir != NULL)
	{
		setenv("OLDPWD", current_dir, 1);
		free(current_dir);
	}
	else
	{
		perror("getcwd");
		return;
	}
	if (chdir(dir) != 0)
	{
		new_dir = getcwd(NULL, 0);
		if (new_dir != NULL)
		{
			setenv("PWD", new_dir, 1);
			free(new_dir);
		}
		else
			perror("getcwd");
	}
}

/**
 * set_initial_dir - sets the initial directory
 */
void set_initial_dir(void)
{
	char *current_dir = getcwd(NULL, 0);

	if (current_dir != NULL)
	{
		setenv("PWD", current_dir, 1);
		setenv("OLDPWD", current_dir, 1);
		free(current_dir);
	}
	else
	{
		perror("getcwd");
		exit(1);
	}
}
