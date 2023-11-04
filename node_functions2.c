#include "shell.h"

/**
 * delete_node - deletes a node from a list
 *
 * @head: a pointer to the head of the list
 * @var: the name of the node to delete
 *
 * Return: true if the node was deleted.
 * alse is returned if the node was not found
 */
bool delete_node(node **head, const char *var)
{
	node *prev = NULL, *current = *head;

	if (!(head && *head))
		return (false);


	while (current)
	{
		if (!_strcmp(current->var, var))
			break;
		prev = current;
		current = current->next;
	}
	if (!current)
		return (false);
	if (!prev)
		*head = current->next;
	else
		prev->next = current->next;
	if (current->var)
		free(current->var);
	if (current->val)
		free(current->val);
	free(current);
	return (true);
}
/**
 * join_arr - this function creates a linked list from an array of strings
 *
 * @array: an array of strings
 *
 * Return: the head of a linked list. NULL is returned if the array is empty
 */
node *join_arr(char **array)
{
	node *head = NULL;
	char *str, *var, *val, **arr;
	int i;

	if (!array || !array[0] || !array[0][0])
		return (NULL);
	for (i = 0; array[i]; i++)
	{
		str = _strdup(array[i]);
		arr = split_line(str, "=", 1);
		var = arr[0];
		val = arr[1];
		add_end(&head, var, val);
		free(str);
		free(arr);
	}
	return (head);
}
node *create_env_list(char **env)
{
    node *head = NULL;
    char *var, *val, **arr;
    int i;

    for (i = 0; env[i]; i++)
    {
        arr = split_line(env[i], "=", 1);

        if (arr[0] != NULL && arr[1] != NULL) {
            var = _strdup(arr[0]);
            val = _strdup(arr[1]);
            add_end(&head, var, val);
            free(var);
            free(val);
        }

        free(arr);
    }

    return (head);
}
/**
 * create_arr - Creates an array of strings from a linked list.
 *
 * @head: Pointer to the head of a linked list.
 *
 * Return: A null-terminated array of strings.
 *         NULL is returned if the list is empty.
 */
char **create_arr(node *head)
{
	char **array, *buffer;
	size_t buf_size, arr_size, index = 0;
	int buf_ind, i;

	if (!head)
		return (NULL);

	arr_size = 1;
	/*Start with one element for NULL termination*/
	/*Calculate the required size of the array*/
	while (head)
	{
		arr_size++;
		head = head->next;
	}
	array = malloc(arr_size * sizeof(void *));
	while (head)
	{
		buf_size = 2 + _strlen(head->var) + _strlen(head->val);
		buffer = malloc(FRCHAR(buf_size));
		buf_ind = 0;
		for (i = 0; head->var[i]; i++)
			buffer[buf_ind++] = head->var[i];
		buffer[buf_ind++] = '=';
		for (i = 0; head->val[i]; i++)
			buffer[buf_ind++] = head->val[i];
		buffer[buf_ind] = '\0';
		array[index++] = buffer;
		head = head->next;
	}
	array[index] = NULL;
	return (array);
}
