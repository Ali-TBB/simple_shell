#include "shell.h"
#include <stdio.h>

/**
 * _strtok - tokenizes a string.
 * @str: the string to tokenize.
 * @delim: the delimiter characters.
 * Return: pointer to the next token or NULL if no more tokens.
 */
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}

/**
 * _strcmp - compares two strings.
 * @s1: the first string.
 * @s2: the second string.
 * Return: an integer less than, equal to, or greater than zero
 * if s1 is found to be less than, equal to, or greater than s2, respectively.
 */
int _strcmp(const char *s1, const char *s2)
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
	while (*original == *substring)
	{
		original++;
		substring++;
	}
	return (original);
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
char **malloc_arg()
{
	int arg_count = 0, i;
	char **arg;

	arg_count += 20;
	arg = (char **)malloc((arg_count) * sizeof(char *));
	for (i = 0;i < arg_count ; i++)
	{
		arg[i] = NULL;
	}
	return (arg);
}