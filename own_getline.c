#include "shell.h"
#define BUFSIZE 1024
/**
 * getlines - read all lines from stdin.
 *
 * Description: When file is terminal, this function
 * acts like getline(3), reading just one line.
 * When file is a pipe or regular file, all the content is
 * consumed at a go.
 *
 * @fd: the file descriptor
 *
 * Return: a buffer holding all contents of the file.
 * NULL is returned if malloc failed or if EOF is reached.
 */
char *getlines(int fd)
{
	char *buffer;
	size_t offset, size;
	int step;
	ssize_t bytesread;
	struct stat fdstat;

	fstat(fd, &fdstat);
	if (fdstat.st_size == 0)
		size = 1024;
	else
		size = fdstat.st_size + 1;
	buffer = malloc(size);
	offset = 0;
	step = size;

	if (!buffer)
		return (NULL);

	while (true)
	{
		bytesread = read(fd, &buffer[offset], step);
		if (bytesread == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytesread < step)
			break;
		offset += step;
		buffer = _realloc(buffer, size, size + step);
		size += step;
		if (!buffer)
			return (NULL);
	}
	buffer[offset + bytesread - 1] = '\0';
	return (buffer);
}

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
