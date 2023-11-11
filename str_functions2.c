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
 * _atoi - converts a string into an integer
 * Description;'A function'
 * @s: the string to be converted
 * Return: the integer converted from the string
 */
int _atoi(char *s)
{
	int sign = 1;
	int result = 0;

	while (*s)
	{
		if (*s == '-')
		{
			sign *= -1;
		}
		else if (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
		}
		else if (result > 0)
		{
			break;
		}
		s++;
	}
	return (sign * result);
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
