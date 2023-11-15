#include "shell.h"
#define FRPTR(n) (n * sizeof(void *))

/**
 * appendStr - append a string to an array of strings
 *
 * @arr: a pointer to a malloced array of strings
 * @size: a pointer to an integer holding the size of the array
 * @str: the new string to append to the array
 * @index: the index at which to insert the string
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool appendStr(char ***arr, size_t *size, char *str, int index)
{
	size_t arr_size;
	char **array;

	arr_size = *size;
	array = *arr;

	if (!(arr && *arr))
		return (false);
	while (arr_size <= (unsigned int)index)
	{
		if (arr_size == 0)
			arr_size++;
		array = _realloc(array,
			FRPTR(arr_size),
			FRPTR(arr_size) * 2);
		arr_size *= 2;
		if (!array)
			return (false);
	}
	(array)[index] = str;
	*arr = array;
	*size = arr_size;
	return (true);
}
/**
 * split_line - Splits a str into an array of substr based on a delimiter.
 * @input: The input string to be split.
 * @delimiter: The delimiter used for splitting.
 * @max: The maximum number of splits (0 for unlimited).
 *
 * Return: A dynamic alloc array of strings containing the substrings,
 *         or NULL on failure.
 */
char **split_line(char *input, char *delimiters, unsigned int max_splits);
/**
 * split_line - split a input using a delimiters
 *
 * @input: the input to split
 *
 * @delimiters: a list of delimiterss to use to split the input
 *
 * @max_splits: the max_splitsimum number of times the input should be splitted
 * Set this to 0 to split infinitely *
 * Return: A null-terminated array of inputs.
 * NULL is returned if malloc failed or if the input
 * could not be split; this could be because:
 * - the input is empty
 * - the input is NULL
 * - the input only contains delimiterss
 * - delimiterss is NULL
 * - delimiterss is empty
 */
char **split_line(char *input, char *delimiters, unsigned int max_splits)
{
	char **array, prev = '\0', curr, *token;
	size_t tok_index = 0, tok_count = 2;
	bool in_quotes = false;
	unsigned int  str_index, i;

	if (!(input && *input && delimiters && *delimiters))
		return (NULL);
	array = malloc(FRPTR(tok_count));
	if (array == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
	token = strtok(input, delimiters);

	while (token != NULL)
	{
		for (str_index = 0; token[str_index]; str_index++)
		{
			curr = token[str_index];
			if (curr == '\"' && prev != '\\')
			{
				in_quotes = !in_quotes;
				continue;
			}
			if (!in_quotes)
			{
				for (i = 0; delimiters[i]; i++)
					if (curr == delimiters[i])
					{
						input[str_index] = '\0';
						break;
					}
			}
		}
		appendStr(&array, &tok_count, token, tok_index++);
		if (max_splits && max_splits + 1 == tok_index)
			break;
		token = strtok(NULL, delimiters);
	}
	if (tok_index)
		appendStr(&array, &tok_count, NULL, tok_index);
	else
	{
		free(array);
		array = NULL;
	}
	return (array);
}