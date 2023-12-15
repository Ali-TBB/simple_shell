#include "shell.h"

/**
 * execuet_and - Executes an AND command.
 * @data: Pointer to the data_of_program struct.
 * @command: Pointer to the AND command.
 * Return: Integer status code.
 */
int execuet_and(data_of_program *data, com_list *command)
{
	int ret_ex;

	ret_ex = execute_help(data, command);
	if (ret_ex == -1 || ret_ex == 0)
	{
		ret_ex = execute_help(data, command->next);
		execute(data, command->next);
		if (ret_ex == -1 || ret_ex == 0)
		{
			execute(data, command);
			return (ret_ex);
		}
	}
	return (ret_ex);
}

/**
 * execuet_or - Executes an OR command.
 * @data: Pointer to the data_of_program struct.
 * @command: Pointer to the OR command.
 * Return: Integer status code.
 */
int execuet_or(data_of_program *data, com_list *command)
{
	int ret_ex;

	ret_ex = execute_help(data, command);
	if (ret_ex == 0 || ret_ex == -1)
		execute(data, command);
	else
	{
	_print_error(ret_ex, data, command);
	ret_ex = execute_help(data, command->next);
	execute(data, command->next);
	}
	return (ret_ex);
}
/**
 * execuet_with - Executes a WITH command.
 * @data: Pointer to the data_of_program struct.
 * @command: Pointer to the WITH command.
 * Return: void.
 */
void execuet_with(data_of_program *data, com_list *command)
{
	int ret_ex;

	ret_ex = execute_help(data, command);
	if (ret_ex == 0 || ret_ex == -1)
	{
		execute(data, command);
	}
	else
		_print_error(ret_ex, data, command);
	ret_ex = execute_help(data, command);

}
