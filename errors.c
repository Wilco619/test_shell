#include "shell.h"

/**
 * eputs_ - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void eputs_(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eputchar_(str[i]);
		i++;
	}
}

/**
 * eputchar_ - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int eputchar_(char c)
{
	static int i;
	static char buf[BUFFER_W];

	if (c == FLUSH || i >= BUFFER_W)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putfile_descripter_ - writes the character c to given file_d
 * @c: The character to print
 * @file_d: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putfile_descripter_(char c, int file_d)
{
	static int i;
	static char buf[BUFFER_W];

	if (c == FLUSH || i >= BUFFER_W)
	{
		write(file_d, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putsfile_descripter_ - prints an input string
 * @str: the string to be printed
 * @file_d: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int putsfile_descripter_(char *str, int file_d)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putfile_descripter_(*str++, file_d);
	}
	return (i);
}