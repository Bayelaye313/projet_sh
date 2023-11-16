#include "shell.h"
/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
/**
 * _atoi - convert to a int
 * @s:string
 * Return:int
 */
int _atoi(char *s)
{
int i, j, n, x;

	i = n = 0;
	x = 1;
	while ((s[i] < '0' || s[i] > '9') && (s[i] != '\0'))
	{
		if (s[i] == '-')
			x *= -1;
		i++;
	}
	j = i;
	while ((s[j] >= '0') && (s[j] <= '9'))
	{
		n = (n * 10) + x * ((s[j]) - '0');
		j++;
	}
	return (n);
}
/**
 * join_char - appends a character to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @chr: the character to add to the string
 * @index: the index at which to insert the character
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool join_char(char **string, size_t *size, char chr, int index)
{
	size_t new_size = *size + 1;
	/*Increase the size to accommodate the new character*/
	int i;
	char *new_string = realloc(*string, new_size + 1);
	/*Allocate memory for the updated string*/

	if (new_string == NULL)
	{
		return (false);
	}

	*string = new_string; /*Update the pointer with the new memory location*/

	for (i = *size; i >= index; i--)
	{
		(*string)[i + 1] = (*string)[i];
	}

	(*string)[index] = chr; /*Insert the new character*/

	(*string)[new_size] = '\0'; /*Ensure the string is null-terminated*/

	*size = new_size; /*Update the size*/

	return (true); /*Operation succeeded*/
}
/**
 * findquote - finds an unescaped quote in a string
 * @str: the string to search
 * @quote: the quote to search for (could be " or ')
 * Return: the index where the unescaped quote was found, or -1
 *		if the quote wasn't found.
 */
int findquote(char *str, char quote)
{
	int i;
	char a, s, c;

	if (!str || !*str)
		return (-1);

	c = (quote == '"') ? '"' : '\'';

	for (i = 0; str[i] != '\0'; i++)
	{
		a = str[i];
		s = str[i + 1];

		if (a == c)
			return (i);
		if (s == c && a != '\\')
			return (i + 1);
		else if (s)
			i++;
	}

	return (-1);
}

