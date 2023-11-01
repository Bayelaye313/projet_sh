#include "shell.h"
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
        return -1;

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
char **split_line(char *input, char *delimiter, unsigned int max)
{
    char **array, prev = '\0', a;
    size_t arr_size = 2;
    unsigned int arr_ind = 0, str_ind, i;
    bool flipped;
    bool group_quote = true;
    int quote_index;

    if (!(input && *input && delimiter && *delimiter))
        return (NULL);
    
    array = malloc(FRPTR(arr_size));

    for (str_ind = 0; input[str_ind]; str_ind++)
    {
        a = input[str_ind];
        flipped = false;
        for (i = 0; delimiter[i]; i++)
            if (a == delimiter[i])
            {
                input[str_ind] = '\0';
                flipped = true;
                break;
            }
        if (prev == '\0' && flipped == false)
        {
            size_t arr_size_old = arr_size;
            char **array_old = array;
            arr_size = arr_ind + 2;
            array = _realloc(array_old, FRPTR(arr_size_old), FRPTR(arr_size));
            if (!array)
            {
                free(array_old);
                return (NULL);
            }
            array[arr_ind++] = &input[str_ind];
        }

        if (group_quote && (!flipped && (a == '\'' || a == '"')))
        {
            quote_index = findquote(input + str_ind + 1, a);
            if (quote_index != -1)
                str_ind += quote_index + 1;
        }

        if (max && max + 1 == arr_ind)
            break;

        prev = input[str_ind];
    }

    if (arr_ind)
    {
        size_t arr_size_old = arr_size;
        char **array_old = array;
        arr_size = arr_ind + 1;
        array = _realloc(array_old, FRPTR(arr_size_old), FRPTR(arr_size));
        if (!array)
        {
            free(array_old);
            return (NULL);
        }
        array[arr_ind] = NULL;
    }
    else
    {
        free(array);
        array = NULL;
    }

    return (array);
}
