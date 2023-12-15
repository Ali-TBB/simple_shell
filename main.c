#include "shell.h"
#include <stdio.h>

/**
 * main - entry point of the program.
 * @argc: the number of command-line arguments.
 * @argv: an array of command-line arguments.
 * @env: an array of environment variables.
 * Return: exit status.
 */
int main(int argc, char *argv[], char *env[])
{

	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	data_init(data, argc, argv, env);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;

	run(prompt, data);

	return (0);
}

/**
 * data_init - initializes the data structure.
 * @data: Pointer to the data_of_program struct.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * @env: Array of environment variables.
 */
void data_init(data_of_program *data, int argc, char *argv[], char *env[])
{
	int i = 0;
	list_t *current;

	data->prog_name = _strdup(argv[0]);
	data->exec_counter = 0;
	data->input_line = NULL;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{	data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{	_printe(data->prog_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
		}
	data->env = NULL;
	data->alias_list = NULL;
	data->commande = add_comande_end(data);
	data->commande->comande_num = 0;
	data->commande->commande_name = argv[0];
	data->envp = (char **)malloc(sizeof(char **) * (i + 1));
	if (env)
	{
		for (; env[i]; i++)
		{
			data->envp[i] = _strdup(env[i]);
		}
	}
	data->envp[i] = NULL;
	i = 0;
	while (env[i] != NULL)
	{	current = add_nodeint_end(&data->env);
		current->var = strtok(env[i], "=");
		current->value = strtok(NULL, "=");
		i++;
	}
	env = data->envp;
}

/**
 * run - Continuously reads input, prints the prompt,
 * and executes a specified operation.
 * @prompt: The prompt to be printed.
 * @data: Pointer to the data_of_program struct.
 */
void run(char *prompt, data_of_program *data)
{
	ssize_t read;

	while (++(data->exec_counter))
	{

		_print(prompt);

		read = _getline(data);

		if (read > 0)
		{
			execute_help1(data);
		}
		else if (read == EOF)
		{
			break;
		}
	}
	free_all_data(data);
	exit(errno);
}
