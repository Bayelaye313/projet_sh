#include "shell.h"
/**
 * proces_string - Write a string to a file.
 *
 * This function takes a string and writes it character by character to the
 * provided file pointer until it reaches the null terminator.
 *
 * @file: A pointer to the FILE where the string will be written.
 * @str: The string to be processed.
 */
void proces_string(FILE *file, const char *str)
{
	while (*str != '\0')
	{
		my_fputc(*str, file);
		str++;
	}
}
/**
 * process_format - Process formatted string and write to file.
 *
 * @file: Pointer to FILE.
 * @format: Format string.
 * @args: va_list of arguments.
 */
void process_format(FILE *file, const char *format, va_list args)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			switch (*(++format))
			{
				case 'd':
				case 'i':
					process_integer(file, va_arg(args, int));
					break;
				case 's':
					proces_string(file, va_arg(args, const char *));
					break;
			}
		} else
		{
			my_fputc(*format, file);
		}
		format++;
	}
}
/**
 * my_fprintf - Imprime une chaîne formatée dans un fichier FILE.
 * @file: Le fichier dans lequel écrire
 * @format: La chaîne de format
 * @...: Les arguments variables à formater
 */
void my_fprintf(FILE *file, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	process_format(file, format, args);
	va_end(args);
}
/**
 * myprintf - Custom implementation of printf function.
 * @str: The formatted string to be printed.
 * @...: Additional arguments based on format specifiers in str.
 * Return: Always returns 0.
 */
int myprintf(const char *str, ...)
{
	va_list args;

	va_start(args, str);
	process_format(stdout, str, args);
	va_end(args);
	return (0);
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
/**
 * fprinterr - print an error message to stderr
 *
 * @message: the message to print
 *
 * Return: nothing
 */
void fprinterr(char *message)
{
	write(STDERR_FILENO, message, _strlen(message));
	free(message);
}
