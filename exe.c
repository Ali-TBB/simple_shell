#include "shell.h"
#include <stdio.h>



int execute(data_of_program *data, com_list *command)
{
    int status, i = 0, a = 0, j;
    char path[1024];
    char *envp[] = {NULL};
    char *args[20];
    pid_t child_pid;

    for (j = 0; j < 20; j++)
	{
        args[j] = NULL;
    }
	if (command->arg != NULL)
	{
	args[a] = _strdup(command->commande_name);
    while (command->arg[a] != NULL)
	{
        args[a + 1] = _strdup(command->arg[a]);
        a++;
    }
	}
    if (check_alias(data, command) || set_env(data,command))
	{
        return (1);
    }
    if (searchFileInPath(command, data)) {
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
            for (j = 0; j < 20; j++)
			{
                free(args[j]);
            }

            i = 1;
        }
    } else {
        printf("%s: %s: command not found.\n", data->prog_name, command->commande_name);
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
