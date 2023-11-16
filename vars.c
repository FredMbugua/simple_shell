#include "shell.h"

/**
 * is_chain - test if current character in the buffer is a chain delimeter
 * @info: struct parameter
 * @buf: the buffer
 * @p: the address of the current position in the buffer
 *
 * Return: 1, if chain delimiter, otherwise, 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CDM_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * check_chain - checks if chain should continue based on the last status
 * @info: the first parameter, a struct
 * @buf: the second parameter, buffer
 * @p: the third parameter, current position in buf
 * @i: the fourth parameter,starting position in buf
 * @len: the last parameter, length of buf
 *
 * Return: nothing
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t g = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}
	*p = g;
}

/**
 * replace_alias - replaces an alias in a tokenized string
 * @info: parameter struct
 *
 * Return: 1 if alias is replaced, otherwise, 0
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in tokens
 * @info: the first parameter, struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->arg[i][1])
		{
			continue;
		}
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &(info->argv[i][i]), '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&(info->argv[i]), _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: the original string
 * @new: the string that replaces the one in @old
 *
 * Return: 1 if replaced
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
