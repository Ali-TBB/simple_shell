#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


/************* MACROS **************/
#include "macros.h"

/************* STRUCTURES **************/

/**
 * struct list_s - A structure representing a command node in a list.
 * @path: The path associated with the command.
 * @arg: An array of strings representing command arguments.
 * @commande_name: The name of the command.
 * @falg_type: The flag type indicating the type of command
 * (CHAIN_AND, CHAIN_OR, CHAIN_WITH, CHAIN_NR).
 * @comande_num: The execution number of the command.
 * @next: Pointer to the next command node in the list.
 *
 * This structure represents a command node in a linked list used to store
 * information about individual commands. It includes details such as the
 * command's path, arguments, name, flag type, execution number, and a link
 * to the next command in the list.
 */
typedef struct list_s
{
	char *path;
	char **arg;
	char *commande_name;
	int falg_type;
	int comande_num;
	struct list_s *next;
} com_list;

/**
 * struct list_env - A structure representing a node in
 * an environment variables list.
 * @var: The name of the environment variable.
 * @value: The value associated with the environment variable.
 * @next: Pointer to the next node in the environment variables list.
 *
 * This structure represents a node in a linked list used
 * to store information
 * about environment variables. It includes the variable name,
 * associated value,
 * and a link to the next node in the list.
 */
typedef struct list_env
{
	char *var;
	char *value;
	struct list_env *next;
} list_t;
/**
 * struct info - A structure representing essential information
 * for program execution.
 * @prog_name: The name of the program.
 * @input_line: Pointer to the input line read from the user.
 * @exec_counter: The execution counter, counting the number
 * of program executions.
 * @file_descriptor: The file descriptor used for input (e.g., stdin).
 * @env: Pointer to a linked list of environment variables.
 * @alias_list: Pointer to a linked list of alias information.
 * @commande: Pointer to a linked list of command execution information.
 *
 * This structure holds key information required for
 * the execution of a program,
 * including the program name, input line, execution counter, file descriptor,
 * environment variables list, alias list, and command execution list.
 */

typedef struct info
{
	char *prog_name;
	char *input_line;
	int exec_counter;
	int file_descriptor;
	list_t *env;
	list_t *alias_list;
	com_list *commande;
} data_of_program;

/*========  main.c  ========*/

void data_init(data_of_program *data, int ac, char *av[], char *env[]);
void run(char *prompt, data_of_program *data);


/*========  linked_list.c  ========*/

list_t *add_nodeint_end(list_t **head);
list_t *get_nodeint_at_var(list_t *head, char *var);
com_list *add_comande_end(data_of_program *data);
void free_listcom(com_list *head);
void free_listint(list_t *head);

/*========  string.c  ========*/

char *removeSubstring(char *original, const char *substring);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);


/*========  string1.c  ========*/
char *_strdup(const char *str);
char *_strchr(const char *str, int c);
int _strlen(const char *s);
char *removestring(const char *buffer, const char *substring);

/*========  alias.c  ========*/

void get_alias(data_of_program *data);
int check_alias(data_of_program *data, com_list *command);
void set_alias(data_of_program *data, char *var, char *value);
int print_alias(data_of_program *data, char *arg);
int print_all_alias(data_of_program *data);

/*========  env.c  ========*/

void get_env(data_of_program *data);
char *_getenv(char *env, data_of_program *data);
int set_env(data_of_program *data, com_list *command);

/*========  fun1.c  ========*/

void get_chain(data_of_program *data);
void insert_command_and(com_list *current, char *buffer);
void insert_command_or(com_list *current, char *buffer);
void insert_command_with(com_list *current, char *buffer);
void insert_all_command(data_of_program *data);
void insert_command_nr(com_list *current, char *buffer);
char **malloc_arg();
int _clear(com_list *current);
int changeDirectory(com_list *command, data_of_program *data);

/*========  exe.c  ========*/

int execute(data_of_program *data, com_list *command);
void execute_help(data_of_program *data);


/*========  check_path.c  ========*/
int fileExistsInDirectory(const char *filename, const char *directory);
int searchFileInPath(com_list *current, data_of_program *data);
void handlarg(com_list *command);
void print_all(data_of_program *data);

#endif
