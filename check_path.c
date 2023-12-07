#include "main.h"

int fileExistsInDirectory(const char *filename, const char *directory)
{
	FILE *file;
	char path[1024];

	snprintf(path, sizeof(path), "%s/%s", directory, filename);
	file = fopen(path, "r");
	if (file != NULL) {
		fclose(file);
		return 1;
	} else {
		return 0;
	}
}

int searchFileInPath(list_t **head)
{
	char *path = getenv("PATH");
	char *token;
	int found;
	list_t *current = *head;

	if (path == NULL) {
		fprintf(stderr, "PATH environment variable not set\n");
		return 0;
	}
	while (current != NULL)
	{
		token = strtok(path, ":");
		found = 0;
		while (token != NULL)
		{
			if (fileExistsInDirectory(current->filename, token))
			{
				current->path = strdup(token);
				found = 1;
				break;
			}

			token = strtok(NULL, ":");
		}

		if (!found)
		{
			current->path = NULL;
		}

		current = current->next;
	}

	return 1;
}

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
