#include "shell.h"



int execute(data_of_program *data, com_list *command)
{
    int i;

    command->comande_num = 0;
    i = check_alias(data, command);
    if (i == 1)
    {
        command->comande_num = 0;
        printf("alias command\n");
        return (1);
    }
    if (i == -1)
    {
        printf("%s: %s: commnd not found\n", data->prog_name, command->commande_name);
        return (1);
    }
    printf("%s: %s: command not found\n", data->prog_name, command->commande_name);
    return (0);
}

/*    char path[1024];
    char *envp[] = {NULL};
    pid_t child_pid;
    int status;
    list_t *current = *head;

    while (current != NULL)
    {
        if (current->path != NULL)
        {
            snprintf(path, sizeof(path), "%s/%s", current->path, current->filename);
            child_pid = fork();
            if (child_pid == 0)
            {
                if (execve(path, current->argv, envp) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                wait(&status);
            }
        }
        else
        {
            printf("bash: %s: command not found.\n", current->filename);
        }
        current = current->next;
    }*/
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
