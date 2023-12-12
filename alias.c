#include "shell.h"
#include <string.h>

/**
 * get_alias - processes and updates the input line
 * by replacing alias variables.
 * @data: the data of the program.
 */
void get_alias(data_of_program *data)
{
	list_t *current;
	com_list *command;
	char *alias;
	char *buffer;

	command = data->commande;
	while (command)
	{
		buffer = command->commande_name;
		current = data->alias_list;
		while (current)
		{
			alias = current->var;
			if (strcmp(alias, buffer) == 0)
			{
				free(command->commande_name);
				command->commande_name = strdup(current->value);
				break;
			}
			current = current->next;
		}
		command = command->next;
	}
}
/**
 * get_alias - processes and updates the input line
 * by replacing environment variables.
 * @data: the data of the program.
 */
void set_alias(data_of_program *data, char *var, char *value)
{
	list_t *current;

	current = data->alias_list;
	current = add_nodeint_end(&current);
	current->value = value;
	current->var = var;
}
/**
 * get_alias - processes and updates the input line
 * by replacing environment variables.
 * @data: the data of the program.
 */
int check_alias(data_of_program *data, com_list *command)
{
    list_t *alias = data->alias_list;
    char *value;
    char *var;
    int len, i = 0;

	if (_strcmp(command->commande_name, "alias") == 0)
	{
		if (command->arg == NULL)
		{
			print_all(data);
			return (1);
		}
		while (command->arg[i])
		{
			if (strchr(command->arg[i], '=') == NULL)
				return (print_alias(data, command->arg[i]));
			var = _strtok(command->arg[i], "=");
			value =_strtok(NULL, "=");
			printf("good\n");
			len = strlen(var);
			while (alias)
			{
				if (_strcmp(var, alias->var) == len)
				{
					free(alias->value);
					alias->value = strdup(value);
					return (1);
				}
				alias = alias->next;
			}
			if (alias == NULL)
			{
				set_alias(data, var, _strtok(value, "="));
				return (1);
			}
			i++;
		}
	}
    return (0);
}
/**
 * print_alias - Print alias values based on the given command.
 * @data: Pointer to the data_of_program struct.
 *
 * This function prints alias values based on the provided command.
 * It iterates over the command list, extracts relevant tokens, and
 * prints corresponding alias values if found.
 *
 * Return: 1 if aliases are found, 0 otherwise.
 */
int print_alias(data_of_program *data, char *arg)
{
	list_t *alias;
	int a = -1;

	alias = data->alias_list;
	while (alias)
	{
		if (_strcmp(alias->var, arg) == 0)
		{
			printf("alias %s='%s'\n",alias->var, alias->value);
			a = 1;
		}
		alias = alias->next;
	}

	return (a);
}
int print_all_alias(data_of_program *data)
{
	list_t *alias = data->alias_list;
	int a = 0;

	while (alias)
	{
		printf("alias %s='%s'\n",alias->var, alias->value);
		alias = alias->next;
		a = 1;
	}
	return (a);
}