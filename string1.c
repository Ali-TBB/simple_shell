#include "shell.h"
#include <stdlib.h>

/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i] != '\0')
		i++;

	return (i);
}
/**
 * _strdup - create allocated copy of string
 * @str: the pointer of string want to copy
 * Return: a pointer of string copy
 */
char *_strdup(const char *str)
{
	int i, len;
	char *new;

	if (!str)
		return (NULL);

	len = _strlen(str);

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);

	for (i = 0; i < len; i++)
		new[i] = str[i];

	new[len] = '\0';

	return (new);
}
/**
 * str_reverse - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_reverse(char *string)
{

	int i = 0, length = _strlen(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
