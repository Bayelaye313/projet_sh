#include "shell.h"
/**
 * my_fputs - Writes a string to the specified file descriptor.
 *
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 */
void my_fputs(const char *str, int fd)
{
	size_t len = 0;
	const char *ptr = str;

	while (*ptr != '\0')
	{
		len++;
		ptr++;
	}
	write(fd, str, len);
}

/**
 * _putc - Writes a single character to the specified file descriptor.
 *
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 */
void _putc(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * _putchar - Writes a single character to the standard output.
 *
 * @c: The character to be written.
 *
 * Return: On success, returns the number of charact. On error, returns -1.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * my_fputc - Writes a single character to the specified FILE stream.
 *
 * @c: The character to be written.
 * @file: The FILE stream to write to.
 */
void my_fputc(char c, FILE *file)
{
	(void)file;
	_putchar(c);
}
/**
 * print_error - Print an error message to stderr.
 *
 * @message: Error message string.
 */
void print_error(const char *message)
{
	write(STDERR_FILENO, message, _strlen(message));
}
