#include "shell.h"
#include <stdio.h>



int execute(data_of_program *data, com_list *command)
{
	int status, i = 0;
	char path[1024];
	char *envp[] = {NULL};
	pid_t child_pid;

	command->comande_num = 0;
	if (check_alias(data, command))
		return (1);
	if (searchFileInPath(command, data))
	{
		snprintf(path, sizeof(path), "%s/%s", command->path, command->commande_name);
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(path, command->arg, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else 
			{
			i = 1;
			}
		}
		else
		{
			wait(&status);
		}
	}
	else
	{
	printf("bash: %s: command not found.\n", command->commande_name);
	}
	return (i);
}

void execute_help(data_of_program *data)
{
	com_list *command1 = data->commande;
	com_list *command2;

	get_env(data);
	get_chain(data);
	get_alias(data);
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
			}else
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
