#include "shell.h"

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

char *_strchr(const char *str, int c)
{
    while (*str != '\0')
	{
        if (*str == c)
		{
            return ((char *)str);
        }
        str++;
    }

    if (c == '\0')
	{
        return ((char *)str);
    }

    return (NULL);
}
char *removestring(const char *buffer, const char *substring)
{
    size_t bufferLen = _strlen(buffer);
    size_t subLen = _strlen(substring);
    size_t i = 0;
    size_t j = 0;
	char *result;

    if (buffer == NULL || substring == NULL)
	{
        return (NULL);
    }
    result = (char*)malloc(bufferLen + 1);
    if (result == NULL)
	{
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    while (i < bufferLen)
	{
        if (strncmp(&buffer[i], substring, subLen) == 0)
		{
            i += subLen;
        } else
		{
            result[j++] = buffer[i++];
        }
    }
    result[j] = '\0';
    return (result);
}
