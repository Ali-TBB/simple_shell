#include "shell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>



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
	char *token, *tok;
	int found;

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return (0);
	}
	tok = strtok(current->commande_name, "/");
	tok = strtok(NULL, "/");
	if (tok != NULL)
	{
		current->path = _strdup(current->commande_name);
		while (tok != NULL)
		{
			current->commande_name = _strdup(tok);
			tok = strtok(NULL, "/");
		}
		return (1);
	}
	token = strtok(path, ":");
	found = 0;
	while (token != NULL)
	{
		if (fileExistsInDirectory(current->commande_name, token))
		{
			current->path = _strdup(token);
			found = 1;
			break;
		}
		token = strtok(NULL, ":");
	}
	if (!found)
	{
		current->path = NULL;
	}
	return (found);
}
