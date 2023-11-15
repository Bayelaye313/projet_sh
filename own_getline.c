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
    static ssize_t offset = 0;
    static ssize_t bytesread = 0;
    size_t result_offset = 0, size = 1024;
    char c, *temp, *result = malloc(size);

    if (!result)
        return NULL;
    
    while (1)
    {
        if (offset >= bytesread)
        {
            bytesread = read(fd, buffer, BUFSIZE);
            offset = 0;
            if (bytesread <= 0)
            {
                result[result_offset] = '\0';
                break;
            }
        }

        c = buffer[offset++];
        
        if (c == '\n')
        {
            result[result_offset] = '\0';
            break;
        }

        result[result_offset++] = c;

        if (result_offset >= size - 1)
        {
            size *= 2;
            temp = realloc(result, size);
            if (!temp)
            {
                free(result);
                return NULL;
            }
            result = temp;
        }
    }

    return result;
}