#include "shell.h"
#define BUFSIZE 1024
/**
 * remove_quotes - remove quotes surrounding a string
 *
 * @string: target string
 *
 * Return: nothing
 */
char *remove_quotes(char *string)
{
	char c;
	int i;

	if (!string || !string[0])
		return (NULL);
	c = string[0];
	if (c != '"' && c != '\'')
		return (string);
	i = findquote(string + 1, c);
	if (c == -1)
		return (string);
	string[i + 1] = '\0';
	string[0] = '\0';
	return (&string[1]);
}
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
    char *name = strtok(str, "=");
    char *value = strtok(NULL, "\0");
    node *current;

    if (name == NULL || value == NULL)
    {
        fprintf(stderr, "Erreur : Format d'alias incorrect\n");
        return (-1);
    }

    /*Supprimer les guillemets simples ou doubles de la valeur de l'alias*/
    if ((value[0] == '\'' || value[0] == '\"') && value[strlen(value) - 1] == value[0])
    {
        value[strlen(value) - 1] = '\0';
        value++;
    }

    /*Vérifier si l'alias existe déjà*/
    current = info->aliase;

    while (current != NULL)
    {
        if (strcmp(current->var, name) == 0)
        {
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
		if (current->var && current->val)
		{
			printf("%s='%s'\n", current->var, current->val);
		}

		current = current->next;
	}
}

int _alias(state_t *info, char **args) {
	int i;

	if (args[0] == NULL) {
		/*Si l'utilisateur appelle juste "alias", imprimer tous les alias*/
		print_aliases(info->aliase);
	} else {
		for (i = 0; args[i] != NULL; i++) {
			char *name = strtok(args[i], "=");
			char *value = strtok(NULL, "\0");

			if (name == NULL || value == NULL || value[0] == '\0') {
				fprintf(stderr, "Erreur : Format d'alias incorrect\n");
				return (-1);
			}
			value = remove_quotes(value);
			if (value == NULL) {
				/*Si il n'y a pas de '=' dans l'argument, c'est une demande d'afficher l'alias*/
				node *alias = get_node(info->aliase, name);

				if (alias != NULL) {
					printf("%s='%s'\n", alias->var, alias->val);
				} else {
					fprintf(stderr, "Erreur : Alias '%s' non trouvé\n", name);
					return (1);
				}
			} else {
				/*Si on a trouvé un '=', c'est une tentative de définition d'alias*/
				if (set_alias(info, make_format("%s=%s", name, value)) == -1) {
					fprintf(stderr, "Erreur lors de la définition de l'alias\n");
					return (1);
				}
			}
		}
	}

	return 0;
}
