#include "shell.h"
/**
 * add_nodeint_end - add node in the end.
 * @head: head of double pointer
 * Return: the address of the new element.
 */
list_t *add_nodeint_end(list_t **head)
{
	list_t *ptr;
	list_t *new;

	if (head == NULL)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	if (*head == NULL)
	{
	*head = new;
		return (new);
	}
	ptr = *head;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
	return (new);
}

/**
 * free_listint - free linked lest.
 * @head: linked list.
 * Return: void.
 */
void free_listint(list_t *head)
{
	list_t *next;

	while (head != NULL)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
/**
 * get_nodeint_at_var - print list
 * @head: linked list.
 * @var: the var of the node,
 * Return: node of index.
 */
list_t *get_nodeint_at_var(list_t *head, const char *var)
{
	if (head == NULL || var == NULL)
		return (NULL);

	while (head != NULL)
	{
		if (_strcmp(head->var, var) == 0)
		{
			return (head);
		}
		head = head->next;
	}

	return (NULL);
}

/**
 * add_comande_end - Add a new command node at the end of the list.
 * @data: Pointer to the data_of_program struct containing the command list.
 *
 * This function adds a new command node at the end of the command list
 * in the data_of_program struct. If the list is empty, it creates the
 * list and returns a pointer to the new node.
 *
 * Return: Pointer to the new command node.
 */
com_list *add_comande_end(data_of_program *data)
{
	com_list *ptr;
	com_list *new;

	new = malloc(sizeof(com_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	if (data->commande == NULL)
	{
		data->commande = new;
		return (new);
	}
	ptr = data->commande;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
	return (new);
}
/**
 * free_listcom - free linked lest.
 * @head: linked list.
 * Return: void.
 */
void free_listcom(com_list *head)
{
	com_list *next;

	while (head != NULL)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
