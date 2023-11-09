#include "shell.h"
/**
 * _realloc - Resizes a previously allocated block of memory
 *
 * @ptr: Pointer to the previously allocated memory block
 * @old_size: Size of the old memory block
 * @new_size: Size of the new memory block
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	size_t copy_size, i;

	if (!new_size && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size || !ptr)
	{
		return (ptr);
	}
	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}
	copy_size = old_size < new_size ? old_size : new_size;
	for (i = 0; i < copy_size; i++)
	{
		p[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (p);
}
/**
 * _memset - fills a given string with n number of fill chars
 * @str: string to be filled with fill
 * @fill: the char to put into str
 * @n: the number of chars to fill
 */
void _memset(char *str, int fill, int n)
{
	int i;

	for (i = 0; i < n; i++)
		str[i] = fill;
}
/**
 * _memcpy - copies part or all of string src to string dest
 * @dest: destination string
 * @src: source string
 * @bytes: number of bytes to copy
 */
void _memcpy(char *dest, char *src, unsigned int bytes)
{
	unsigned int i;

	for (i = 0; i < bytes; i++)
		dest[i] = src[i];
}
