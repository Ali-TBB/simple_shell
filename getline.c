#include "macros.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * _getline - Reads a line from the input file descriptor, replaces newlines
 *            with semicolons, and updates the data structure.
 *
 * @data: Pointer to the data_of_program struct.
 * Return: The length of the input line read, or EOF if an error occurs.
 */
int _getline(data_of_program *data)
{
	int c, i, a = 0;
	char *buffer;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (buffer == NULL)
	{
		return (EOF);
	}

	c = read(data->file_descriptor, buffer, BUFFER_SIZE);
	data->input_line = (char *)malloc(c * sizeof(char *));
	for (i = 0; i < c; i++)
	{
		if (buffer[i] == '\n')
		{
			if (i + 1 < c)
			{
				data->input_line[a++] = ';';
				data->input_line[a++] = ' ';
				i++;
			} else
			{
				break;
			}
		}
		data->input_line[a++] = buffer[i];
	}
	free(buffer);
	if (c == 0 && a == 0)
	{
		return (EOF);
	}

	data->input_line[a] = '\0';
	return (a);
}
