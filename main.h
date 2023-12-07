#ifndef MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LINE_LENGTH 256

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *path;
    char **argv;
	char *filename;
	struct list_s *next;
} list_t;


char **realloc_arr(int length , char **Array);
void execute(list_t **head);
int tokenArray(char *line);
char *_strtok(char *str, const char *delim);
int fileExistsInDirectory(const char *filename, const char *directory);
int searchFileInPath(list_t **head);
void get_command(list_t **head, char **Array);
void freeList(list_t *head);
#define MAIN_H
#endif