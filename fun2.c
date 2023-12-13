#include "shell.h"
/**
 * insert_command_and - Parses the input line to extract
 * commands for the AND chain.
 * @buffer: command line.
 * @current: data struct of command.
 * Return: void.
 */
void insert_command_and(com_list *current, char *buffer)
{
	char *toke;
	int i;

	if (current->falg_type == CHAIN_AND)
	{
		current->arg = malloc_arg();
		toke = strtok(buffer, " ");
		current->commande_name = _strdup(toke);
		toke = strtok(NULL, " ");
		i = 0;
		if (toke != NULL)
		{
		while (toke != NULL)
		{
			current->arg[i] = toke;
			toke = strtok(NULL, " ");
			i++;
		}
		}
		else
			current->arg = NULL;
	}
}
/**
 * insert_command_or - Parses the input line to
 * extract commands for the OR chain.
 * @buffer: command line.
 * @current: data struct of command.
 * Return: void.
 */
void insert_command_or(com_list *current, char *buffer)
{
	char *tok;
	int i;

	if (current->falg_type == CHAIN_OR)
	{
		current->arg = malloc_arg();
		tok = strtok(buffer, " ");
		current->commande_name = _strdup(tok);
		tok = strtok(NULL, " ");
		i = 0;
		if (tok != NULL)
		{
		while (tok != NULL)
		{
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
		}
		else
			current->arg = NULL;
	}
}
/**
 * insert_command_with - Parses the input line to extract
 * commands for the WITH chain.
 * @buffer: command line.
 * @current: data struct of command.
 * Return: void.
 */
void insert_command_with(com_list *current, char *buffer)
{
	char *toke;
	int i;

	if (current->falg_type == CHAIN_WITH)
	{
		current->arg = malloc_arg();
		toke = strtok(buffer, " ");
		current->commande_name = _strdup(toke);
		toke = strtok(NULL, " ");
		i = 0;
		if (toke != NULL)
		{
		while (toke != NULL)
		{
			current->arg[i] = toke;
			toke = strtok(NULL, " ");
			i++;
		}
		}
		else
			current->arg = NULL;
	}
}
/**
 * insert_command_nr - Parses the input line to extract
 * commands for the WITH chain.
 * @buffer: command line.
 * @current: data struct of command.
 * Return: void.
 */
void insert_command_nr(com_list *current, char *buffer)
{
	char *tok;
	int i;

	if (current->falg_type == CHAIN_NR && current->comande_num != 0)
	{
		tok = strtok(buffer, " ");
		current->commande_name = _strdup(tok);
		tok = strtok(NULL, " ");
		i = 0;
		current->arg = malloc_arg();
		if (tok != NULL)
		{
		while (tok != NULL)
		{
			current->arg[i] = _strdup(tok);
			tok = strtok(NULL, " ");
			i++;
		}
		}
		else
			current->arg = NULL;
	}
}
/**
 * _clear - Clear the standard output if
 * the command is "clear".
 * @current: Pointer to the com_list structure representing the command.
 *
 * This function checks if the command name is "clear" and
 * clears the standard output
 * (stdout) if needed.
 * Return: 1 if success , 0 otherwise.
 */
int _clear(com_list *current)
{
	const char *clearSeq = "\033[H\033[J";

	if (current != NULL && current->commande_name != NULL &&
		_strcmp(current->commande_name, "clear") == 0)
	{

		write(STDOUT_FILENO, clearSeq, 7);
		return (1);
	}
	return (0);
}
