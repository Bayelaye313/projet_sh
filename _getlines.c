#include "shell.h"
#define BUFSIZE 1024
char *_getlines(int fd)
{
    static char buffer[BUFSIZE];
    static ssize_t index = 0;
    static ssize_t lecteur = 0;
    size_t result_index = 0, size = 1024;
    char c, *temp, *result = malloc(size);

    if (!result)
        return NULL;
    
    while (1)
    {
        if (index >= lecteur)
        {
            lecteur = read(fd, buffer, BUFSIZE);
            index = 0;
            if (lecteur <= 0)
            {
                result[result_index] = '\0';
                break;
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
                return NULL;
            }
            result = temp;
        }
    }

    return (result);
}