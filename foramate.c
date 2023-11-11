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
