#include "shell.h"

/**
 * get_env - processes and updates the input line
 * by replacing environment variables.
 * @data: the data of the program.
 */

void get_env(data_of_program *data)
{
	char *str = _strdup(data->input_line);
	char *buffer = _strdup(data->input_line);
	char *tok, *temp;
	int len = 0, i;

	if (data == NULL || data->input_line == NULL || data->env == NULL)
		return;
	while (*buffer != '$')
	{
		if (*buffer == '\0')
			return;
		buffer++;
		len++;
	}
	buffer++;
	tok = strtok(buffer, " ");
	tok = _getenv(tok, data);
	if (tok == NULL)
		return;
	temp = (char *)malloc(strlen(str) + strlen(tok) + 1);
	if (temp == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < len - 1; i++)
		temp[i] = str[i];
	temp = strcat(temp, " ");
	temp = strcat(temp, tok);
	while (*buffer != ' ')
	{
		if (*buffer == '\0')
			break;
		buffer++;
	}
	if (*buffer != '\0')
		temp = strcat(temp, buffer);
	free(data->input_line);
	data->input_line = _strdup(temp);
	get_env(data);
}
/**
 * _getenv - Get the value of an environment variable.
 * @env: Name of the environment variable.
 * @data: Pointer to the data_of_program struct.
 *
 * This function retrieves the value of
 * the specified environment variable from the
 * environment list in the data structure.
 *
 * Return: Value of the environment variable or NULL if not found.
 */
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
/**
 * set_env - Set or update an environment variable in the data structure.
 * @data: Pointer to the data_of_program struct.
 * @command: Current command from the command list.
 *
 * This function sets or updates an environment
 * variable in the data structure based on
 * the provided command.
 *
 * Return: 1 if the environment variable is set or updated, 0 otherwise.
 */
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
