#include "shell.h"
/**
 * is_delimiter - Vérifie si un caractère est un délimiteur.
 * @c: Le caractère à vérifier.
 * @cutter: La chaîne de délimiteurs.
 *
 * Return: 1 si c est un délimiteur, 0 sinon.
 */
static int is_delimiter(char c, const char *cutter)
{
	const char *ptr = cutter;

	while (*ptr != '\0')
	{
		if (c == *ptr)
			return (1);
		ptr++;
	}
	return (0);
}

/**
 * skip_delimiters - Ignore les délimiteurs au début d'une chaîne.
 * @string: La chaîne à traiter.
 * @cutter: La chaîne de délimiteurs.
 *
 * Return: Un pointeur vers le premier caractère non délimiteur.
 */
static char *skip_delimiters(char *string, const char *cutter)
{
	while (*string != '\0' && is_delimiter(*string, cutter))
		string++;
	return (string);
}

/**
 * find_end_of_token - Trouve la fin du jeton.
 * @string: La chaîne à traiter.
 * @cutter: La chaîne de délimiteurs.
 *
 * Return: Un pointeur vers la fin du jeton.
 */
static char *find_end_of_token(char *string, const char *cutter)
{
	while (*string != '\0' && !is_delimiter(*string, cutter))
		string++;
	return (string);
}

/**
 * _strtok - Découpe une chaîne en jetons.
 * @string: La chaîne à découper.
 * @cutter: La chaîne de délimiteurs.
 *
 * Return: Un pointeur vers le premier caractère du prochain jeton, ou NULL.
 */
char *_strtok(char *string, const char *cutter)
{
	static char *token;
	char *start, *end;

	start = (string != NULL) ? string : token;
	if (start == NULL)
		return (NULL);
	start = skip_delimiters(start, cutter);
	if (*start == '\0')
	{
		token = NULL;
		return (NULL);
	}
	end = find_end_of_token(start, cutter);

	if (*end != '\0')
	{
		*end = '\0';
		token = end + 1;
	} else
	{
		token = NULL;
	}
	return (start);
}
