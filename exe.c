#include "main.h"



void execute(list_t **head)
{
    char path[1024];
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
    }
}
