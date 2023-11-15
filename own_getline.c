#include "shell.h"
#define BUFSIZE 1024
/**
 * _getline - Reads a line of text from a file descriptor.
 * @fd: File descriptor to read from.
 * Return: A dynamically allocated string containing the line read,
 *         or NULL on failure.
 */
char *_getline(int fd);
char *_getline(int fd)
{
	static char buffer[BUFSIZE];
	static ssize_t index;
	static ssize_t lecteur;
	size_t result_index = 0, size = 1024;
	char c, *temp, *result = malloc(size);

	if (!result)
		return (NULL);
	while (1)
	{
		if (index >= lecteur)
		{
			lecteur = read(fd, buffer, BUFSIZE);
			index = 0;
			if (lecteur <= 0)
			{
				free(result);
				return(NULL);
			}
		}

		c = buffer[index++];
		if (c == '\n')
		{
			result[result_index] = '\0';
			break;
		}

		result[result_index++] = c;

		if (result_index >= size - 1)
		{
			size *= 2;
			temp = realloc(result, size);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			result = temp;
		}
	}
return (result);
}
