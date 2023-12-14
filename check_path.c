#include "shell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
/**
 * fileExistsInDirectory - Check if a file exists in a specific directory.
 * @filename: Name of the file to check.
 * @directory: Directory to check for the file.
 *
 * This function checks if a file with the given name exists in the specified
 * directory.
 * Return: 1 if the file exists, 0 otherwise.
 */
int fileExistsInDirectory(const char *filename, const char *directory)
{
	FILE *file;
	char path[1024];

	snprintf(path, sizeof(path), "%s/%s", directory, filename);
	file = fopen(path, "r");
	if (file != NULL)
	{
		fclose(file);
		return (1);
	}

	return (0);
}
/**
 * searchFileInPath - Search for a file in the directories
* listed in the PATH variable.
 * @current: Current command from the command list.
 * @data: Pointer to the data_of_program struct.
 *
 * This function searches for the executable file in
 * the directories listed in the PATH
 * variable. If found, updates the command with
 * the full path to the executable file.
 *
 * Return: 1 if the file is found and updated, 0 otherwise.
 */
int searchFileInPath(com_list *current, data_of_program *data)
{
	char *path;
	char *token, *tok;
	int found;

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
	path = _getenv("PATH", data);
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
