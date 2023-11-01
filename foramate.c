#include "shell.h"
/**
 * process_integer - Convert an integer to a string and write it to a file.
 *
 * This function takes an integer and converts it to its string representation
 * and writes it to the provided file pointer.
 *
 * @file: A pointer to the FILE where the integer will be written.
 * @num: The integer to be processed.
 */
void process_integer(FILE *file, int num)
{
	char buffer[20];
	int i = 0;

	do {
		buffer[i++] = '0' + num % 10;
		num /= 10;
	} while (num != 0);
	while (i > 0)
	{
		my_fputc(buffer[--i], file);
	}
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
 * make_format - resolves format specifiers in a string
 * @fm: the format string
 * Return: a new string with format specifiers replaced
 * with actual value
 */
char *make_format(const char *fm, ...)
{
	size_t size = 4;
	char *buffer = malloc(FRCHAR(size)), chr, nxt, *s;
	int b_index, index, i;
	va_list args;

	if (!fm || !fm[0])
		return (NULL);
	index = b_index = 0;
	chr = fm[index++];
	nxt = fm[index];
	va_start(args, fm);
	for (index = 0; fm[index]; index++)
	{
		chr = fm[index];
		nxt = fm[index + 1];
		if (chr == '%')
		{
			if (nxt == 'd')
			{
				b_index += join_int(&buffer, &size, va_arg(args, int), b_index);
			}
			else if (nxt == 's')
			{
				s = va_arg(args, char *);
				for (i = 0; s[i]; i++)
					join_char(&buffer, &size, s[i], b_index++);
			}
			index++;
		}
		else
			join_char(&buffer, &size, chr, b_index++);
	}
	va_end(args);
	join_char(&buffer, &size, '\0', b_index);
	return (buffer);
}
