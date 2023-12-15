#include "shell.h"
#include <stdlib.h>
/**
 * free_all_data - Frees all memory associated with the data structure.
 *
 * @data: Pointer to the data_of_program struct.
 * Return: void.
 */
void free_all_data(data_of_program *data)
{

	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->prog_name);
	}
	free_listint(data->env);
	free_listint(data->alias_list);
	free_listcom(data->commande);
	free(data->input_line);

	free(data->prog_name);

}
