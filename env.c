#include "shell.h"
#include <stdlib.h>
#include <string.h>
/**
 * get_env - processes and updates the input line 
 * by replacing environment variables.
 * @data: the data of the program.
 */

void get_env(data_of_program *data)
{

	char *str = _strdup(data->input_line);
	char *buffer = _strdup(data->input_line);
	char *temp;
    int destIndex = 0;
    list_t *current;

    if (data == NULL || data->input_line == NULL || data->env == NULL)
	{
        return;
    }
    str = _strdup(data->input_line);
	buffer = _strdup(data->input_line);
    while (*str)
	{
        if (*str == '$')
		{
            char *str1 = strtok(++str, " ");
            if (str1 != NULL)
			{
                current = get_nodeint_at_var(data->env, str1);
                if (current != NULL)
				{
                    temp = removestring(buffer, current->value);
                    if (temp != NULL)
					{
                        free(buffer);
                        buffer = temp;
                        destIndex = strlen(buffer);
                    }
                }
                free(str1);
            }
        } else {
            buffer[destIndex++] = *str++;
        }
    }

    buffer[destIndex] = '\0';
    free(data->input_line);
    data->input_line = _strdup(buffer);
    free(str);
    free(buffer);
}

char *_getenv(char *env, data_of_program *data)
{
	list_t *current;
	char *path;

	current = get_nodeint_at_var(data->env, env);
	if (current)
	{
		path = _strdup(current->value);
		return (path);
	}
	else
		return (NULL);
}
int set_env(data_of_program *data, com_list *command)
{
	char *var;
	char *value;
	char *buffer = _strdup(command->commande_name);
	int i = 0;
	list_t *env = data->env;
	list_t *new;

	if (strstr(buffer, "="))
	{
		var = strtok(buffer, "=");
		value = strtok(NULL, "");
		while (env)
		{
			if (_strcmp(var, env->var) == 0)
			{
				free(env->value);
				env->value = _strdup(value);
				i = 1;
			}
			env = env->next;
		}
		if (env == NULL)
		{
			new = add_nodeint_end(&data->env);
			new->value = _strdup(value);
			new->var = _strdup(var);
			i = 1;
		}
	}
	free(buffer);
	return (i);
}