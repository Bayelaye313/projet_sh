#include "shell.h"
/**
 * add_end - Adds a new node to the end of a linked list.
 *
 * @head: Pointer to a pointer to the head of the linked list.
 * @var: Variable name for the new node.
 * @val: Value for the new node.
 *
 * Return: Point to the newly added node, or NULL if memory alloc fails.
 */
node *add_end(node **head, const char *var, const char *val)
{
	node *new_node = malloc(sizeof(node));

	if (!new_node)
		return (NULL);
	new_node->var = _strdup(var);
	new_node->val = _strdup(val);
	new_node->next = NULL;
	if (!(new_node->var && new_node->val))
	{
		free(new_node->var);
		free(new_node->val);
		free(new_node);
		return (NULL);
	}
	if (*head == NULL)
		*head = new_node;
	else
	{
		node *current = *head;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	return (new_node);
}
/**
 * get_node - Retrieves a node with a specific variable name.
 *
 * @head: Pointer to the head of the linked list.
 * @var: Variable name to search for.
 *
 * Return: Point to the node with the specified var name, or NULL if not found.
 */
node *get_node(node *head, const char *var)
{
	if (!head)
		return (NULL);
	if (!_strcmp(head->var, var))
		return (head);
	return (get_node(head->next, var));
}
/**
 * set_node - Sets existing node or adds a new node if variable doesn't exist.
 *
 * @head: Pointer to a pointer to the head of the linked list.
 * @var: Variable name.
 * @val: New value for the variable.
 * Return: Point to the updated or newly node, or NULL if memory alloc fails.
 */
node *set_node(node **head, const char *var, const char *val)
{
	node *existing_node = get_node(*head, var);

	if (!head)
		return (NULL);
	if (!existing_node)
		return (add_end(head, var, val));
	if (existing_node->val)
		free(existing_node->val);
	existing_node->val = _strdup(val);
	return (existing_node);
}
/**
 * set_val - Sets the default value for a variable if it doesn't already exist.
 *
 * @head: Pointer to a pointer to the head of the linked list.
 * @var: Variable name.
 * @val: Default value for the variable.
 *
 * Return: Pointer to the existing or newly added node.
 */
node *set_val(node **head, const char *var, const char *val)
{
	node *existing_node = get_node(*head, var);

	if (existing_node != NULL)
	{
		return (existing_node);
	}
	return (add_end(head, var, val));
}
