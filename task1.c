#include <stdio.h>
#include "main.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
/**
 * check_process_exec - checks to execute the process
 * @user_input: input from user
 * @input_toks: pointer to input
 * Return: -1
 */
int check_process_exec(char *user_input, char **input_toks)
{
	pid_t childpid;
	int status;
	int c;

	childpid = fork();
	if (childpid == -1)
	{
		perror("child process could not be created");
		return (-1);
	}
	if (childpid == 0)
	{
		c = execve(user_input, input_toks, __environ);
		if (c == -1)
		{
			perror("execve: ");
			return (-1);
		}
	}
	else
	{
		wait(&status);
		free(user_input);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (!isatty(STDIN_FILENO))
			return (status);
	}
	return (0);
}
/**
 *handle_command - this function checks the command passed by the user
 *@input: the user command passed by the user
 *@US_INPUT: USER INPUT
 *Description: ignore __attribute__ when unused
 *@argv: the arguments from main
 */
void handle_command(char **input, char *US_INPUT,
		char **argv __attribute__((unused)))
{
	char *USER_INPUT;

	if (strcmp(input[0], "cd") == 0)
	{
		builtin_cd(input);
	}
	else if (INPUT_BUILTIN(input))
	{
		if (HANDLE_BUILTIN(input) == EXIT_CODE)
		{
			mem_check(input, US_INPUT);
			exit(0);
		}
	}
	else
	{
		USER_INPUT = handle_path(*input);
		if (USER_INPUT != NULL)
		{
			check_process_exec(USER_INPUT, input);
		}
		else
			HANDLE_ERROR();
	}
}
/**
 * main - This is the main function
 * @argc: checks the number of arguments passed to main
 * @argv: pointer to each arguments passed to the main
 * @envp: pointer to environment
 * Return: 0 on success
 */
int main(__attribute__((unused)) int argc,
		__attribute__((unused)) char **argv,
		__attribute__((unused)) char **envp)
{
	char *USER_INPUT = NULL;
	size_t INPUT_SIZE;
	size_t LEN_INPUT = 0;
	char **token;
	int STAT = 0;
	char *delim;

	set_initial_dir();
	INPUT_SIZE = LEN_INPUT = 0;
	signal(SIGINT, handle_sigint);
	delim = " \n";
	while (1)
	{
		LEN_INPUT++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", strlen("$ "));
			fflush(stdout);
		}
		_getline(&USER_INPUT, &INPUT_SIZE, STAT);
		token = tokenizeAndvalidate(USER_INPUT, delim);
		if (*token == NULL)
			STAT = 0;
		else
		{
			handle_command(token, USER_INPUT, argv);
		}
		mem_check(token, USER_INPUT);
		USER_INPUT = NULL;
	}
	return (0);
}
/**
 * tokenizeAndvalidate - this function tokenize(splits) the read inputs
 * @input: the USER_INPUT read by the getline function
 * @delim: the delimiter
 * Return: access to the input command
 */
char **tokenizeAndvalidate(char *input, char *delim)
{
	char *token, *str_t;
	size_t i, l, count;
	char **tok_d;

	tok_d = NULL;
	check_malloc(&str_t, strlen(input) + 1, "INPUT FAIL");
	strcpy(str_t, input);
	count = token_number(str_t, delim);
	tok_d = second_malloc(tok_d, count + 1, "SECOND MALLOC FAILED");
	strcpy(str_t, input);
	token = strtok(str_t, delim);
	for (i = 0; i < count; i++)
	{
		tok_d[i] = (char *) malloc(sizeof(char *) * strlen(token) + 1);
		if (tok_d[i] == NULL)
		{
			for (l = 0; l < i; l++)
				free(tok_d[l]);
			free(token);
			free(tok_d);
			perror("Error: Malloc failed");
			return (NULL);
		}
		strcpy(tok_d[i], token);
		token = strtok(NULL, delim);
	}
	free(str_t);
	tok_d[count] = NULL;
	return (tok_d);
}

/**
 * HANDLE_ERROR - error function handler
 */
void HANDLE_ERROR(void)
{
	char *s = "Error: command cannot be found";

	write(STDERR_FILENO, s, strlen(s));
}
