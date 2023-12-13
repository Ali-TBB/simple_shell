#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * _strtok - tokenizes a string.
 * @str: the string to tokenize.
 * @delim: the delimiter characters.
 * Return: pointer to the next token or NULL if no more tokens.
 */

/*
char *_strtok(char *text, char *delimiters)
{
    int len_tx;
    int i = 0;
    int len_tok;
    char *ptr;
    int len_tex_new = 0;
    char *tex_new;

    int c = 0, lo = 0, len_del = 0, del = 0, o = 0;

    if (text == NULL || delimiters == NULL)
    {
        return NULL;
    }

    len_tx = strlen(text);
    len_del = strlen(delimiters);

    for (i = 0; i < len_tx; i++)
    {

        for (del = 0; del < len_del;)
        {
            if (text[i] == delimiters[del])
            {
                text[i] = '\0';
                len_tok = strlen(text);
                ptr = (char *)malloc(len_tok + 1);

                if (ptr == NULL)
                {
                    return NULL;
                }

                for (o = 0; o < (len_tok + 1); o++)
                {
                    ptr[o] = text[o];
                }
                len_tex_new = (len_tx - len_tok);
                if (ptr[0] == '\0')
                {

                    tex_new = (char *)malloc(len_tex_new);

                    if (tex_new == NULL)
                    {
                        free(ptr);
                        return NULL;
                    }

                    i++;

                    for (c = 0; c < len_tex_new; c++)
                    {
                        *(tex_new + c) = text[i + c];
                    }
                    for (lo = 0; lo < len_tex_new; lo++)
                    {
                        *(text + lo) = *(tex_new + lo);
                    }
                    free(tex_new);
                    free(ptr);
                    i = 0;
                    del = 0;
                    continue;
                }

                tex_new = (char *)malloc(len_tex_new);

                if (tex_new == NULL)
                {
                    free(ptr);
                    return NULL;
                }

                i++;

                for (c = 0; c < len_tex_new; c++)
                {
                    *(tex_new + c) = text[i + c];
                }
                for (lo = 0; lo < len_tex_new; lo++)
                {
                    *(text + lo) = *(tex_new + lo);
                }
                free(tex_new);

                return (ptr);
            }
            del++;
        }
    }
    return (NULL);
}
*/
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