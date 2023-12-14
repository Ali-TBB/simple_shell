#include "shell.h"
/**
 * _strcmp - compares two strings.
 * @s1: the first string.
 * @s2: the second string.
 * Return: an integer less than, equal to, or greater than zero
 * if s1 is found to be less than, equal to, or greater than s2, respectively.
 */
int _strcmp(char *s1, char *s2)
{

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * removeSubstring - removes a substring from the original string.
 * @original: the original string.
 * @substring: the substring to remove.
 * Return: a new string with the substring removed.
 */
char *removeSubstring(char *original, const char *substring)
{
	char *laststring;

	while (*original == *substring)
	{
		original++;
		substring++;
	}
	laststring = _strdup(original);
	return (laststring);
}

/**
 * _strcat - concatenates two strings.
 * @dest: the destination string.
 * @src: the source string.
 * Return: pointer to the concatenated string (dest).
 */
char *_strcat(char *dest, const char *src)
{
	char *result = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (result);
}
/**
 * malloc_arg - Allocate memory for an array of strings.
 *
 * This function allocates memory for an array of strings and returns a pointer
 * to the allocated memory.
 *
 * Return: Pointer to the allocated memory for the array of strings.
 */
char **malloc_arg()
{
	int arg_count = 0, i;
	char **arg;

	arg_count += 20;
	arg = (char **)malloc((arg_count) * sizeof(char *));
	for (i = 0; i < arg_count; i++)
	{
		arg[i] = NULL;
	}
	return (arg);
}
/**
 * argNum - Count the number of arguments in a command.
 * @command: Pointer to the com_list representing the command.
 *
 * Return: Number of arguments in the command.
 */
int argNum(com_list *command)
{
	int i = 0;

	if (command->arg == NULL)
		return (2);
	while (command->arg[i] != NULL)
	{
		i++;
	}
	i += 2;
	return (i);
}
