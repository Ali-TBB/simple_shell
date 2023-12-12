#include "macros.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    while (data->input_line[i] != '\n')
    {
        if (data->input_line[i] == '&' && data->input_line[i + 1] == '&')
        {
			new_command = add_comande_end(data);
            new_command->falg_type = CHAIN_AND;
            new_command->comande_num = ++a;
			printf("work good \n");
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
	if (a == 0)
	{
    new_command = add_comande_end(data);
    new_command->falg_type = CHAIN_NR;
    new_command->comande_num = ++a;
	}
    insert_all_command(data);
}
/**
 * insert_command_and - Parses the input line to extract commands for the AND chain.
 * @data: Pointer to the data_of_program struct.
 * Return: void.
 */
void insert_command_and(com_list *current, char *buffer)
{
	char *tok;
	int i;

	printf("%s\n", buffer);
	if (current->falg_type == CHAIN_AND)
	{
		current->arg = malloc_arg();
		tok = strtok(buffer, " ");
		printf("%s\n",tok);
		current->commande_name = tok;
		tok = strtok(NULL, " ");
		i = 0;
		while (tok != NULL)
		{
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
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
		current->commande_name = tok;
		tok = strtok(NULL, " ");
		i = 0;
		while (tok != NULL)
		{
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
	}
}
/**
 * insert_command_with - Parses the input line to extract commands for the WITH chain.
 * @data: Pointer to the data_of_program struct.
 * Return: void.
 */
void insert_command_with(com_list *current, char *buffer)
{
	char *tok;
	int i;

	if (current->falg_type == CHAIN_WITH)
	{
		current->arg = malloc_arg();
		tok = strtok(buffer, " ");
		current->commande_name = tok;
		tok = strtok(NULL, " ");
		i = 0;
		while (tok != NULL)
		{
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
	}
}
/**
 * insert_command_nr - Parses the input line to extract commands for the WITH chain.
 * @data: Pointer to the data_of_program struct.
 * Return: void.
 */
void insert_command_nr(data_of_program *data, com_list *current)
{
	char *tok;
	char *buffer;
	int i;

	buffer = strdup(data->input_line);
	if (current->falg_type == CHAIN_NR && current->comande_num != 0)
	{
		tok = strtok(buffer, " ");
		current->commande_name = strdup(tok);
		tok = strtok(NULL, " ");
		i = 0;
		current->arg = malloc_arg();
		while (tok != NULL)
		{
			printf("arg[%d]: %s\n",i , tok);
			current->arg[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
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
	char *buffer = strdup(data->input_line);
	char *buffer2;
	char *strremove;

	while (current)
	{
		if (current->falg_type == CHAIN_AND && current->comande_num != 0)
		{
			tok = strtok(buffer, "&&");
			buffer2 = strdup(buffer);
			free(buffer);
			strremove = _strcat(tok, "&& ");
			buffer = removeSubstring(buffer2, strremove);
			insert_command_and(current, tok);
			free(buffer2);
		} else if (current->falg_type == CHAIN_OR && current->comande_num != 0)
		{
			tok = strtok(buffer, "||");
			buffer2 = strdup(buffer);
			free(buffer);
			strremove = _strcat(tok, "|| ");
			buffer = removeSubstring(buffer2, strremove);
			insert_command_and(current, tok);
		} else if (current->falg_type == CHAIN_WITH && current->comande_num != 0)
		{
			tok = strtok(buffer, ";");
			buffer2 = strdup(buffer);
			free(buffer);
			strremove = _strcat(tok, "; ");
			buffer = removeSubstring(buffer2, strremove);
			insert_command_and(current, tok);
		} else if (current->falg_type == CHAIN_NR && current->comande_num != 0)
		{
			insert_command_nr(data, current);
		}
		current = current->next;
	}

}
