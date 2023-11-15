#include "shell.h"
/**
 * _strdup - duplicate a string
 *
 * @str: string to duplicate
 *
 * Return: new string or NULL if malloc failed
 */
char *_strdup(const char *str)
{
	char *s;
	unsigned int i = 0, l;
	/*Vérifie si la chaîne source est NULL*/
	if (str == NULL)
		return (NULL);
	/*Calcule la longueur de la chaîne source*/
	l = _strlen(str);
	s = malloc(l + 1);
	if (!s)
	{
		perror("Error in malloc");
		exit(EXIT_FAILURE);
	}
	/*Copie la chaîne source dans la nouvelle chaîne*/
	for (i = 0; i < l; i++)
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}

/**
 * _strlen - it swaps the values of two integers
 * Description:'A function'
 * @s: the string to be checked
 * Return: The lenght of the string
 */
int _strlen(const char *s)
{
	int i, lenght;

	if (s == NULL)
		return (-1);

	lenght = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		lenght++;
	}
	return (lenght);
}

/**
 * _strcmp - compares two strings
 * @s1: the string to be compared
 * @s2: the second string to be compared
 * Description:'A function'
 * Return: j if successful
 */
int _strcmp(const char *s1, const char *s2)
{
	int i, j;

	i = 0;
	j = 0;

	while (j == 0)
	{
		if ((*(s1 + i) == '\0') && (*(s2 + i) == '\0'))
			break;
		j = *(s1 + i) - *(s2 + i);
		i++;
	}
	return (j);
}
/**
 * comment - Identifies a comment in command line
 *
 * @string: the command line string
 * Return: Nothing. It is void
 */
void comment(char *string)
{
	int j;

	if (string == NULL)
		return;
	for (j = 0; string[j]; j++)
		if (string[j] == '#')
			if (j == 0 || string[j - 1] == ' ')
			{
				string[j] = '\0';
				break;
			}
}
