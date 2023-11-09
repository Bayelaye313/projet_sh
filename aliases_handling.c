#include "shell.h"
#define BUFSIZE 1024
/**
 * set_alias - Sets or updates an alias in the shell.
 *
 * @info: Pointer to the shell's state_t structure.
 * @str: String containing the alias in the format "name=value".
 *
 * Return: 0 on success, -1 on failure (incorrect format or memory allocation).
 */
int set_alias(state_t *info, char *str)
{
	/*Analyser la chaîne str pour extraire le nom et la valeur de l'alias*/
	char *name = strtok(str, "=");
	char *value = strtok(NULL, "\0");

	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Erreur : Format d'alias incorrect\n");
		return (-1);
	}

	/*Vérifier si l'alias existe déjà*/
	node *current = info->aliase;

	while (current != NULL)
	{
		if (strcmp(current->var, name) == 0)
		{
			/*L'alias existe déjà, mettez à jour sa valeur*/
			free(current->val);
			current->val = strdup(value);
			return (0);
		}
		current = current->next;
	}

	/*L'alias n'existe pas, ajoutez-le à la fin de la liste*/
	if (add_end(&(info->aliase), name, value) == NULL)
	{
		return (-1);
	}

	return (0);
}
/**
 * print_aliases - Prints the list of aliases.
 *
 * @aliases: Pointer to the head of the linked list containing aliases.
 */
void print_aliases(node *aliases)
{
	node *current = aliases;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->var, current->val);
		current = current->next;
	}
}
