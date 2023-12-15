#include "shell.h"

/**
 * get_chain - gets the command chain from the input data.
 * @data: the data of the program.
 * Return: void.
 */
void get_chain(data_of_program *data)
{
	com_list *new_command = NULL;
	int i = 0, a = 0;

	while (data->input_line[i] != '\0')
	{
		if (data->input_line[i] == '&' && data->input_line[i + 1] == '&')
		{
			new_command = add_comande_end(data);
			new_command->falg_type = CHAIN_AND;
			new_command->comande_num = ++a;
			i += 2;
		}
		else if (data->input_line[i] == '|' && data->input_line[i + 1] == '|')
		{
			new_command = add_comande_end(data);
			new_command->falg_type = CHAIN_OR;
			new_command->comande_num = ++a;
			i += 2;
		}
		else if (data->input_line[i] == ';' && data->input_line[i + 1] == ' ')
		{
			new_command = add_comande_end(data);
			new_command->falg_type = CHAIN_WITH;
			new_command->comande_num = ++a;
			i += 2;
		}
		i++;
	}
	new_command = add_comande_end(data);
	new_command->falg_type = CHAIN_NR;
	new_command->comande_num = ++a;

	insert_all_command(data);
}

/**
 * insert_all_command - Inserts all commands into the command list.
 * @data: Pointer to the data_of_program struct.
 * Return: void.
 */
void insert_all_command(data_of_program *data)
{
	com_list *current = data->commande;
	char *tok;
	char *buffer = _strdup(data->input_line);

	while (current)
	{
		if (current->falg_type == CHAIN_AND && current->comande_num != 0)
		{
			tok = strtok(buffer, "&");
			insert_command_and(current, tok);
		} else if (current->falg_type == CHAIN_OR && current->comande_num != 0)
		{
			tok =  strtok(buffer, "|");
			insert_command_or(current, tok);
		} else if (current->falg_type == CHAIN_WITH && current->comande_num != 0)
		{
			tok =  strtok(buffer, ";");
			insert_command_with(current, tok);
		} else if (current->falg_type == CHAIN_NR && current->comande_num != 0)
		{
			insert_command_nr(current, buffer);
		}
		current = current->next;
	}
	free(buffer);
}
/**
 * changeDirectory - Change the current working
 * directory based on the 'cd' command.
 * @command: Pointer to the com_list structure representing the command.
 * @data: Pointer to the data_of_program structure containing program data.
 *
 * This function checks if the given command is 'cd' and changes
 * the current working
 * directory accordingly. It uses the chdir system call
 * to change the directory.
 * If no argument is provided, it defaults to the home directory.
 *
 * Return: 1 if the directory is successfully changed, 0 otherwise.
 */
int changeDirectory(com_list *command, data_of_program *data)
{
	char *com = _strdup(command->commande_name);

	if (_strcmp(com, "cd") == 0)
	{
		char *newDir = (command->arg != NULL && command->arg[0] != NULL)
		? command->arg[0] : _getenv("HOME", data);

		if (newDir != NULL)
		{
			if (chdir(newDir) != 0)
			{
				perror("chdir");
			}
			return (1);
		}
		else
		{
			fprintf(stderr, "Error: Home directory not found\n");
		}
	}
	return (0);
}
