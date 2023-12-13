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
 * struct list_s - singly linked list
 * @path: path of commande.
 * @arg: arg of commande.
 * @commande_name: commande.
 * @falge_type: type of execute (and , or , with)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
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
 * struct list_env - singly linked list
 * @var: variable .
 * @value: data of the variable
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
 typedef struct list_env
{
	char *var;
    char *value;
	struct list_env *next;
} list_t;
/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
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
list_t *get_nodeint_at_var(list_t *head, const char *var);
com_list *add_comande_end(data_of_program *data);
void free_listcom(com_list *head);
void free_listint(list_t *head);

/*========  string.c  ========*/

char *removeSubstring(char *original, const char *substring);
char *_strtok(char *line, char *delim);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
/*int fileExistsInDirectory(const char *filename, const char *directory);*/

/*========  alias.c  ========*/

void get_alias(data_of_program *data);
int check_alias(data_of_program *data, com_list *command);
void set_alias(data_of_program *data, char *var, char *value);
int print_alias(data_of_program *data, char *arg);
int print_all_alias(data_of_program *data);

/*========  env.c  ========*/

void get_env(data_of_program *data);
char *_getenv(char *env, data_of_program *data);

/*========  fun1.c  ========*/

void get_chain(data_of_program *data);
void insert_command_and(com_list *current, char *buffer);
void insert_command_or(com_list *current, char *buffer);
void insert_command_with(com_list *current, char *buffer);
void insert_all_command(data_of_program *data);
void insert_command_nr(com_list *current, char *buffer);
char **malloc_arg();

/*========  exe.c  ========*/

int execute(data_of_program *data, com_list *command);
void execute_help(data_of_program *data);

/*========  check_path.c  ========*/
int fileExistsInDirectory(const char *filename, const char *directory);
int searchFileInPath(com_list *current, data_of_program *data);
void print_all(data_of_program *data);
#endif