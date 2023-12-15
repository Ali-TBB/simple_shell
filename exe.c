#include "shell.h"
#include <complex.h>

/**
 * execute_help - Executes the 'HELP' command.
 *
 * @data: Pointer to the data_of_program struct.
 * @command: Pointer to the 'HELP' command.
 * Return: Integer status code.
 */
int execute_help(data_of_program *data, com_list *command)
{
	int ret_ex;

	if (command->commande_name == NULL)
		return (-2);
	if (check_alias(data, command) || set_env(data, command) || _clear(command) ||
		changeDirectory(command, data))
	{
		command->comande_num = 0;
		return (-1);
	}
	ret_ex = searchFileInPath(command, data);
	return (ret_ex);

}

/**
 * execute - Execute a command based on the data structure.
 * @data: Pointer to the data_of_program struct.
 * @command: Current command from the command list.
 *
 * This function executes a command based on
 * the provided data structure and command.
 *
 * Return: 1 if the command is executed successfully, 0 otherwise.
 */
void execute(data_of_program *data, com_list *command)
{
	int status, a = 0, arnum = argNum(command);
	char path[1024];
	char **args;
	pid_t child_pid;

	if (command->comande_num == 0)
		return;
	command->comande_num = 0;
	args = init_arg(command, arnum);
	snprintf(path, sizeof(path), "%s/%s", command->path,
	command->commande_name);
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(path, args, data->envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
		for (a = 0; args[a] != NULL; ++a)
			free(args[a]);
		free(args);
	}
}
/**
 * execute_help1 - Helper function to execute a list of commands.
 * @data: Pointer to the data_of_program struct.
 *
 * This function is a helper for executing a
 * list of commands in the data structure.
 * It calls the execute function for each command in the command list.
 */
void execute_help1(data_of_program *data)
{
	com_list *command1 = data->commande;
	int ret_ex;

	get_env(data);
	get_chain(data);
	while (command1)
	{

		if (command1->falg_type == CHAIN_NR && command1->comande_num != 0)
		{
			ret_ex = execute_help(data, command1);
			if (ret_ex == 0 || ret_ex == -1)
				execute(data, command1);
			else
				_print_error(ret_ex, data, command1);
		}
		if (command1->falg_type == CHAIN_AND && command1->comande_num != 0)
		{
			ret_ex = execuet_and(data, command1);
			if (ret_ex != 0)
			{
				_print_error(ret_ex, data, command1);
				return;
			}
		}
		if (command1->falg_type == CHAIN_OR && command1->comande_num != 0)
		{
			ret_ex = execuet_or(data, command1);
			{
				_print_error(ret_ex, data, command1);
				return;
			}
			}
		if (command1->falg_type == CHAIN_WITH && command1->comande_num != 0)
			execuet_with(data, command1);
		command1 = command1->next;
	}
}

/**
 * init_arg - Initializes an array of command arguments based on the given
 *            command structure and argument count.
 *
 * @command: Pointer to the com_list structure representing the command.
 * @arnum:   Number of arguments to be initialized.
 * Return:   Pointer to the array of command arguments.
 */
char **init_arg(com_list *command, int arnum)
{
	int a = 0, j;
	char **args = (char **)malloc(arnum * sizeof(char *));

	for (j = 0; j <= arnum; j++)
		args[j] = NULL;
	args[a] = _strdup(command->commande_name);
	if (command->arg != NULL)
	{
	while (command->arg[a] != NULL)
	{	args[a + 1] = _strdup(command->arg[a]);
		a++;	}
	}
	return (args);
}
