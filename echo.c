#include "shell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>


void print_all(data_of_program *data)
{
    com_list *current = data->commande;
    int i, a = 0;
    char *args;

    while (current)
    {
        printf("name:%s\nflage: %d\nexcute number: %d\nargs: ", current->commande_name, current->falg_type, current->comande_num);
        i = 0;
        if (current->arg != NULL)
        {
        while (current->arg[i] != NULL)
            {
            args = strdup(current->arg[i]);
            printf("%s ", args);
            i++;
            }
        }
        printf("\n");
        a++;
        current = current->next;
    }
}