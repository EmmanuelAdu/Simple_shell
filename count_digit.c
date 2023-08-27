#include <stdlib.h>
#include "main.h"

/**
 * digit_count - counts digits
 * @SIZE: size of count
 * Return: A DIGIT
 */
int digit_count(size_t SIZE)
{
	int digit = 0;

	if (SIZE == 0)
		return (1);
	while (SIZE != 0)
	{
		SIZE /= 10;
		digit++;
	}
	return (digit);
}

/**
 * rev_string - reverses
 * @str: string
 */
void rev_string(char *str)
{
	int i, len;
	char tmp;

	len = 0;
	while (str[len] != '\0')
		len++;
	len--;
	for (i = 0; i < len; i++, len--)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
}

/**
 *_itoa - converts int to a string
 *@command_num: number to convert
 *Return: the converted integer
 */
char *_itoa(size_t command_num)
{
	char *str = malloc(sizeof(char) * (32 + 1));
	int i = 0;

	do {
		str[i++] = command_num % 10 + '0';
		command_num /= 10;
	} while (command_num > 0);
	str[i] = '\0';
	rev_string(str);
	return (str);
}

/**
 *token_number - function that  returns the number of tokens in a string
 *@input: input string
 *@delim: delimiter string
 *Return: -1 if failure and a number if not
 */
size_t token_number(char *input, char *delim)
{
	char *token;
	size_t a;

	a = 0;
	token = strtok(input, delim);
	while (token != NULL)
	{
		a++;
		token = strtok(NULL, delim);
	}
	return (a);
}
