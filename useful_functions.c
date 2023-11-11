#include "shell.h"
/**
 * handle_hashtag - Identifies and removes a comment in a command line.
 * @line: The command line string.
 *
 * Description: This function searches for the first occurrence of '#' in
 * the command line and replaces it with a null terminator to effectively
 * remove any comments.
 */
void handle_hashtag(char *line)
{
	char *comment = _strchr(line, '#');

	if (comment != NULL)
	{
		*comment = '\0';
	}
}

/**
 * rm_quotes - Removes double quotes from a string.
 * @str: The input string.
 *
 * This function removes all occurrences of double quotes.
 *
 * Return: A pointer to the modified string.
 */
char *rm_quotes(char *str)
{
	char *result = str;
	char *write = str;

	if (str == NULL)
		return (NULL);

	while (*str)
	{
		if (*str != '\"')
			*write++ = *str;
		str++;
	}

	*write = '\0';

	return (result);
}
/**
 * join_int - appends an integer to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @num: the integer to insert
 * @index: the index at which to insert the character
 *
 * Return: number of digits appended.
 *		-1 is return if join_char failed.
 */
int join_int(char **string, size_t *size, int num, int index)
{
	int i, temp, len = 0;
	char digit;

	if (num < 0)
	{
		join_char(string, size, '-', index + len);
		num *= -1;
		len++;
	}
	if (num == 0)
	{
		join_char(string, size, '0', index + len);
		return (len + 1);
	}
	temp = num;
	while (temp > 0)
	{
		temp /= 10;
		len++;
	}
	temp = num;
	for (i = 0; i < len; i++)
	{
		digit = '0' + (temp % 10);
		join_char(string, size, digit, index + len - i - 1);
		temp /= 10;
	}
	return (len);
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

