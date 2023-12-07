#include "main.h"
#include <stdio.h>

char **realloc_arr(int length , char **Array)
{
	int Capacity = length * 2;
	int j;
	Array = (char **)realloc(Array, sizeof(char *) * Capacity);

	if (Array == NULL) {
		printf("Memory reallocation failed.\n");
		return (NULL);
	}

	for (j = 0; j < Capacity; j++)
	{
		Array[j] = NULL;
	}
	return (Array);
}


int tokenArray(char *line)
{
	list_t *head = NULL;
	char **Array = (char **)malloc(sizeof(char *) * 10);
	int i = 0;
	int index;
	char *token;

	if (Array == NULL)
	{
		printf("Memory allocation failed.\n");
		return (-1);
	}
	for (i = 0; i < 10; i++)
	{
    Array[i] = NULL;
	}
	i = 0;
	token = _strtok(line, " ");
    while (token != NULL)
	{
		if (i >= 10)
		{
			Array = realloc_arr(i, Array);
		}
		Array[i] = strdup(token);
        if (Array[i] == NULL) {
            fprintf(stderr, "Memory allocation for token failed.\n");
            exit(EXIT_FAILURE);
        }
        i++;
        token = _strtok(NULL, " ");
    }
	
    get_command(&head,Array);
	searchFileInPath(&head);
	execute(&head);
	freeList(head);
	index = i;
	for (i = 0; i < index; i++)
	{
		printf("Token %d: %s\n", i, Array[i]);
	}
	for (i = 0; i < index; i++)
	{
		free(Array[i]);
	}
	free(Array);
	printf("free Arrary good \n");
	return (0);
}

char *_strtok(char *str, const char *delim)
{
    static char *nextToken = NULL;
    char *tokenStart;


    if (str != NULL)
	{
        nextToken = str;
    } else
	{
        if (nextToken == NULL || *nextToken == '\0')
		{
            return (NULL);
        }
    }
    while (*nextToken != '\0' && strchr(delim, *nextToken) != NULL)
	{
        nextToken++;
    }

    if (*nextToken == '\0')
	{
        return (NULL);
    }
    tokenStart = nextToken;
    while (*nextToken != '\0' && strchr(delim, *nextToken) == NULL && *nextToken != '\n')
	{
        nextToken++;
    }
    if (*nextToken == '\0')
	{
        nextToken = NULL;
    } else
	{
        *nextToken = '\0';
        nextToken++;
    }
    return (tokenStart);
}
void freeList(list_t *head)
{
    list_t *current = head;
    list_t *nextNode;
	int i;

    while (current != NULL)
	{
        nextNode = current->next;
		if (current->filename != NULL)
		{
        	free(current->filename);
		}
		if (current->path != NULL)
		{
        	free(current->path);
		}
        if (current->argv != NULL)
		{
            for (i = 0; current->argv[i] != NULL; i++) {
                free(current->argv[i]);
            }
            free(current->argv);
        }

        free(current);
        current = nextNode;
    }
}
