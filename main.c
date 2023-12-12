#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - entry point of the program.
 * @ac: the number of command-line arguments.
 * @av: an array of command-line arguments.
 * @env: an array of environment variables.
 * Return: exit status.
 */
int main(int ac, char *av[], char *env[])
{

	data_of_program data_struct = {NULL}, *data = &data_struct;


	char *prompt = "$";

	data_init(data, ac, av, env);
	run(prompt, data);

	return 0;
}

/**
 * data_init - initializes the data structure.
 * @data: Pointer to the data_of_program struct.
 * @ac: Number of command-line arguments.
 * @av: Array of command-line arguments.
 * @env: Array of environment variables.
 */
void data_init(data_of_program *data, int ac, char *av[], char *env[])
{
	int i = 0;
	list_t *current;
	list_t *alias = NULL;

	data->prog_name = av[0];
	data->exec_counter = 0;
	data->input_line = NULL;
	if (ac == 1)
	{
		data->file_descriptor = STDERR_FILENO;
	}
	else
	{
		data->file_descriptor = open(av[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", data->prog_name, av[1]);
			exit(127);
		}
	}

	data->env = NULL;
	data->alias_list = alias;
	data->commande = add_comande_end(data);
	data->commande->comande_num = 0;
	data->commande->commande_name = av[0];
	while (env[i] != NULL)
	{
		current = add_nodeint_end(&data->env);
		current->var = _strtok(env[i], "=");
		current->value = _strtok(NULL, "=");
		i++;
	}
}

/**
 * run - Continuously reads input, prints the prompt, and executes a specified operation.
 * @prompt: The prompt to be printed.
 * @data: Pointer to the data_of_program struct.
 */
void run(char *prompt, data_of_program *data)
{
	size_t len = 0;
	ssize_t read;


	while (++(data->exec_counter))
	{
		printf("%s", prompt);

		read = getline(&data->input_line, &len, stdin);

		if (read == -1)
		{
			if (feof(stdin))
			{
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		execute_help(data);
		read = 0;
	}
}
