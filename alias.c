#include "shell.h"
#include <stdio.h>

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

			if (alias != NULL)
			{
				printf("alias\n");
				if (_strcmp(alias, buffer) == 0)
				{
					free(command->commande_name);
					command->commande_name = _strdup(current->value);
					break;
				}
			}
			current = current->next;
		}
		command = command->next;
	}
}
/**
 * set_alias - Set an alias in the data structure.
 * @data: Pointer to the data_of_program struct.
 * @var: Alias variable.
 * @value: Alias value.
 *
 * This function sets an alias in the data structure by adding a new node
 * to the alias list with the provided variable and value.
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
 * check_alias - Check for aliases in the given command and update as needed.
 * @data: Pointer to the data_of_program struct.
 * @command: Current command from the command list.
 *
 * This function checks for aliases in the provided command, updates the
 * command if an alias is found, and adds new aliases if needed.
 *
 * Return: 1 if aliases are found or updated, 0 otherwise.
 */
int check_alias(data_of_program *data, com_list *command)
{
	list_t *alias = data->alias_list;
	char *value;
	char *var;
	int i = 0;

	if (_strcmp(command->commande_name, "alias") == 0)
	{
		if (command->arg == NULL)
		{
			print_all_alias(data);
			return (1);
		}
		while (command->arg[i])
		{
			if (strchr(command->arg[i], '=') == NULL)
				return (print_alias(data, command->arg[i]));
			var = strtok(command->arg[i], "=");
			value = strtok(NULL, "");
			while (alias)
			{
				if (_strcmp(var, alias->var) == 0)
				{
					free(alias->value);
					alias->value = _strdup(value);
					return (1);
				}
				alias = alias->next;
			}
			if (alias == NULL)
			{
				set_alias(data, var, value);
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
 * @arg: Argument representing the command or alias to search for.
 *
 * This function prints alias values based on the provided command or alias.
 * It searches for the specified command or alias in the command list,
 * extracts relevant tokens, and prints corresponding alias values if found.
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
			printf("alias %s='%s'\n", alias->var, alias->value);
			a = 1;
		}
		alias = alias->next;
	}

	return (a);
}
/**
 * print_all_alias - Print all alias values stored in the data structure.
 * @data: Pointer to the data_of_program struct.
 *
 * This function prints all alias values stored in the
 * alias list of the data structure.
 * It iterates over the alias list, printing each alias
 * and its corresponding value.
 *
 * Return: 1 if aliases are found, 0 otherwise.
 */
int print_all_alias(data_of_program *data)
{
	list_t *alias = data->alias_list;
	int a = 0;

	while (alias)
	{
		printf("alias %s='%s'\n", alias->var, alias->value);
		alias = alias->next;
		a = 1;
	}
	return (a);
}
