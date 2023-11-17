#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: points to the memory block
 * @b: the byte to fill @s with
 * @n: the amount of bytes to be filled
 *
 * Return: pointer to the memory block
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 *
 * Return: nothing
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc -reallocates a memory block
 * @ptr: points to the previous memory block
 * @old_size: size of the previous block in bytes
 * @new_size: size of the new block in bytes
 *
 * Return: pointer to a block of memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
