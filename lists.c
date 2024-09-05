#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @data: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_node *add_node(list_node **head, const char *data, int index)
{
	list_node *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_node));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_node));
	new_head->index = index;
	if (data)
	{
		new_head->data = _strdup(data);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_node *add_node_end(list_node **head, const char *data, int index)
{
	list_node *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_node));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_node));
	new_node->index = index;
	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_node linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_node *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->data ? h->data : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_node **head, unsigned int index)
{
	list_node *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_node **head_ptr)
{
	list_node *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
