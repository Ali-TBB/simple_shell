#include "shell.h"
/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, _strlen(string)));
}
/**
 * _printe - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, _strlen(string)));
}
/**
 * _print_error - Prints an error message based on the given error code,
 *                data structure, and command structure.
 * @errorcode: Integer representing the error code.
 * @data:      Pointer to the data_of_program struct.
 * @command:   Pointer to the com_list structure representing the command.
 * Return:     Integer status code.
 */
int _print_error(int errorcode, data_of_program *data, com_list *command)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->prog_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(command->commande_name);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
		    _printe(": can't cd to ");
		_printe(command->arg[0]);
		_printe("\n");
		command->commande_name = 0;
	}
	else if (errorcode == 127)
	{
		_printe(data->prog_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(command->commande_name);
		_printe(": not found\n");
		command->comande_num = 0;
	}
	else if (errorcode == 126)
	{
		_printe(data->prog_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(command->commande_name);
		_printe(": Permission denied\n");
		command->comande_num = 0;
	}
	return (0);
}
