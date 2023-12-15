#include "shell.h"
#include <stdio.h>
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
	char *token, *tok, full_path[1024];
	int found;

	tok = strtok(current->commande_name, "/.");
	tok = strtok(NULL, "/.");
	if (tok != NULL)
	{
		current->path = _strdup(current->commande_name);
		while (tok != NULL)
		{
			current->commande_name = _strdup(tok);
			tok = strtok(NULL, "/.");
		}
		handlarg(current);
		return (0);
	}
	path = _getenv("PATH", data);
	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s",
		token, current->commande_name);
		found = check_file(full_path);
		if (found == 0)
		{
			current->path = _strdup(token);
			return (found);
		}
		token = strtok(NULL, ":");
	}
	if (!token)
	{
		current->path = NULL;
	}
	return (found);
}
/**
 * handlarg - Handle args based on the command.
 * @command: Pointer to the com_list structure representing
 * the command.
 *
 */
void handlarg(com_list *command)
{
	char *tok;
	int i;

	tok = strtok(command->commande_name, " ");
	command->commande_name = _strdup(tok);
	tok = strtok(NULL, " ");
	i = 0;
	command->arg = malloc_arg();
	if (tok != NULL)
	{
	while (tok != NULL)
	{
		command->arg[i] = _strdup(tok);
		tok = strtok(NULL, " ");
		i++;
	}
	}
	else
	{
		command->arg = NULL;
	}
}
/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
