#include "macros.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * get_chain - gets the command chain from the input data.
 * @data: the data of the program.
 * @commande: the command list.
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
 * insert_command_and - Parses the input line to extract commands for the AND chain.
 * @data: Pointer to the data_of_program struct.
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
		} else
			current->arg = NULL;
	}
}
/**
 * insert_command_or - Parses the input line to extract commands for the OR chain.
 * @data: Pointer to the data_of_program struct.
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
		} else
			current->arg = NULL;
	}
}
/**
 * insert_command_with - Parses the input line to extract commands for the WITH chain.
 * @data: Pointer to the data_of_program struct.
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
		} else
			current->arg = NULL;
	}
}
/**
 * insert_command_nr - Parses the input line to extract commands for the WITH chain.
 * @data: Pointer to the data_of_program struct.
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
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
		} else
			current->arg = NULL;
	}
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
			tok = strtok(buffer, "&");
			buffer = removeSubstring(tok, "& ");
		} else if (current->falg_type == CHAIN_OR && current->comande_num != 0)
		{
			tok =  strtok(buffer, "|");
			insert_command_and(current, tok);
			tok = strtok(NULL, "");
			buffer = removeSubstring(tok, "| ");
		} else if (current->falg_type == CHAIN_WITH && current->comande_num != 0)
		{
			tok =  strtok(buffer, ";");
			insert_command_and(current, tok);
			tok = strtok(NULL, "");
			buffer = removeSubstring(tok, " ");
		} else if (current->falg_type == CHAIN_NR && current->comande_num != 0)
		{
			insert_command_nr(current, buffer);
		}
		current = current->next;
	}
	free(buffer);
}
