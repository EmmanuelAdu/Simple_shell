#ifndef MAIN_H
#define MAIN_H
#define EXIT_CODE 98

#define MAX_ALIASES 100


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(__attribute__((unused)) int argc,
		__attribute__((unused)) char **argv,
		__attribute__((unused)) char **envp);


char **tokenizeAndvalidate(char *input, char *delim);
extern char **environ;
void execute_command(char **input);
char *handle_path(char *input);
char *_getenv(const char *ptr_env_nm);
void create_path(char **address_path, char **store_tokens, char *input, int i);
char *check_malloc(char **address_path, size_t entire_len, char *message);
ssize_t _getline(char **USER_INPUT, size_t *INPUT_SIZE, int STATS);
int check_valid_path(char *input);
void free_path(char **store_path, char **store_tokens);
void mem_check(char **USER_INPUT, char *US_INPUT);
int INPUT_BUILTIN(char **USER_INPUT);
int HANDLE_BUILTIN(char **USER_INPUT);
int check_process_exec(char *user_input, char **input_toks);
int _builtin_exit(char **toks);
int _builtin_env(__attribute((unused)) char **toks);
void handle_command(char **input, char *US_INPUT, char ** __attribute__((unused)) argv);
void HANDLE_ERROR(void);
void create_envar(char **v, unsigned int l, const char *name, const char *val);
int _env_set_exists(char *v, unsigned int l, const char *name, int overwrite);
int env_does_not_exists(char *env_var, unsigned int envar_length, unsigned int env_length);
void handle_sigint(int signal);
int _setenv(const char *name, const char *value, int overwrite);
char *_itoa(size_t command_num);
void rev_string(char *str);
void handle_definition(char **input);
void print_aliases(void);
void display(void);
int copy_array(char **x, char **y);
int _unsetenv(const char *name);
int _env_name_exists(const char *name);
int len_environ(void);
void set_initial_dir(void);
void builtin_cd(char **args);
int digit_count(size_t SIZE);
size_t token_number(char *input, char *delim);
char **second_malloc(char **array, size_t size_of_malloc, char *error_message);
int is_alias_builtin(const char *command);
void handle_alias_builtin(char **args);
/**
 * inbuilt_command - struct for inbuilt command
 * @id: name of command(inbuilt)
 * @ptr_func: function pointer
 * @input_arrays: array of input commands
 */
struct inbuilt_command
{
	char *id;
	int (*ptr_func)(char **input_arrays);
};

typedef struct
{
	const char *alias_name;
	const char *real_name;
} Alias;
Alias *get_aliases(void);
#endif
