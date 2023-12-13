#include "shell.h"
#include <stdio.h>



int fileExistsInDirectory(const char *filename, const char *directory)
{
	FILE *file;
	char path[1024];

	snprintf(path, sizeof(path), "%s/%s", directory, filename);
	file = fopen(path, "r");
	if (file != NULL)
	{
		fclose(file);
		return 1;
	} else {
		return 0;
	}
}

int searchFileInPath(com_list *current, data_of_program *data)
{
	char *path = _getenv("PATH", data);
	char *token;
	int found;

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return (0);
	}
	token = _strtok(path, ":");
	found = 0;
	while (token != NULL)
	{
		if (fileExistsInDirectory(current->commande_name, token))
		{
			current->path = strdup(token);
			found = 1;
			break;
		}
		token = _strtok(NULL, ":");
	}
	if (!found)
	{
		current->path = NULL;
	}
	return (found);
}
/*
void get_command(list_t **head, char **Array)
{
    list_t *current = *head;
	int a, i = 0, numArgs = 0;


    while (Array[i] != NULL)
	{
        list_t *newNode = (list_t *)malloc(sizeof(list_t));
        if (newNode == NULL)
		{
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        newNode->filename = strdup(Array[i]);
        newNode->argv = (char **)malloc((10) * sizeof(char *));
        if (newNode->argv == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        a = i + 1;
        while (Array[a] != NULL && !(Array[a][0] == '&' && Array[a][1] == '&')) {
            newNode->argv[numArgs] = strdup(Array[a]);
            numArgs++;
            a++;
        }
        newNode->argv[numArgs] = NULL;
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;

        if (Array[a] != NULL)
		{
            i = a + 1;
        } else
		{
            break;
        }
    }
}
*/