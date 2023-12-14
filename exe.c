#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * execute - Execute a command based on the data structure.
 * @data: Pointer to the data_of_program struct.
 * @command: Current command from the command list.
 *
 * This function executes a command based on
 * the provided data structure and command.
 *
 * Return: 1 if the command is executed successfully, 0 otherwise.
 */
int execute(data_of_program *data, com_list *command)
{
	int status, i = 0, a = 0, j, arnum = argNum(command);
	char path[1024];
	char *envp[] = {NULL}, **args = (char **)malloc(arnum * sizeof(char *));
	pid_t child_pid;

	command->comande_num = 0;
	for (j = 0; j < arnum; j++)
		args[j] = NULL;
	args[a] = _strdup(command->commande_name);
	if (command->arg != NULL)
	{
	while (command->arg[a] != NULL)
	{	args[a + 1] = _strdup(command->arg[a]);
		a++;	}
	}
	if (check_alias(data, command) || set_env(data, command) || _clear(command) ||
		changeDirectory(command, data))
		return (1);
	if (searchFileInPath(command, data))
	{
		snprintf(path, sizeof(path), "%s/%s", command->path, command->commande_name);
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(path, args, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else
		{
			wait(&status);
			for (a = 0; args[a] != NULL; ++a)
				free(args[a]);
			free(args);
			i = 1;	}
	} else
		printf("%s: %s: command not found.\n",
			data->prog_name, command->commande_name);
	return (i);
}
/**
 * execute_help - Helper function to execute a list of commands.
 * @data: Pointer to the data_of_program struct.
 *
 * This function is a helper for executing a
 * list of commands in the data structure.
 * It calls the execute function for each command in the command list.
 */
void execute_help(data_of_program *data)
{
	com_list *command1 = data->commande;
	com_list *command2;

	get_env(data);
	get_chain(data);
	/*get_alias(data);*/
	while (command1)
	{
		if (command1->next != NULL)
			command2 = command1->next;
		if (command1->falg_type == CHAIN_NR && command1->comande_num != 0)
		{
			execute(data, command1);
			break;
		}
		if (command1->falg_type == CHAIN_AND && command1->comande_num != 0)
		{
			if (execute(data, command1))
				execute(data, command2);
		}
		if (command1->falg_type == CHAIN_OR && command1->comande_num != 0)
		{
			if (execute(data, command1))
			{
			}
			else
				execute(data, command2);
		}
		if (command1->falg_type == CHAIN_WITH && command1->comande_num != 0)
		{
			execute(data, command1);
			execute(data, command2);
		}
		command1 = command1->next;
	}
}
