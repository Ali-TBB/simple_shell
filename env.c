#include "shell.h"
#include <string.h>
/**
 * get_env - processes and updates the input line 
 * by replacing environment variables.
 * @data: the data of the program.
 */
void get_env(data_of_program *data)
{
    char *str = strdup(data->input_line);
    char *buffer = strdup(data->input_line);
    char *str1 = NULL;
    list_t *current;

    for (; *str; str++)
	{
        if (*str == '$')
		{
            str1 = _strtok(++str, " ");
            if (str1 != NULL)
			{
                current = get_nodeint_at_var(data->env, str1);
                if (current != NULL)
				{
                    buffer = removeSubstring(buffer, current->value);
                }
                free(str1);
                str1 = NULL;
            }
        }
    }
    free(buffer);
}
