#include "shell.h"

/**
 * strtow - splits a string int words while ignoring delimiters
 * @str: the string that is split
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, \0 on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char *s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
	}
	if (numwords == 0)
		return (NULl);
	s = malloc(sizeof(char *) * (numwords + 1));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
		{
			i++;
		}
		k = 0;
		while (!is_delim(str[i], d) && str[i + k])
		{
			k++;
		}
		s[j] = malloc(sizeof(char) * (k + 1));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
			{
				free(s[k]);
			}
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
		{
			s[j][m] = str[i++];
		}
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
