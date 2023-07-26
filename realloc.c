#include "shell.h"

/**
* _setmemory - fills memory with a constant byte
* @s: the pointer to the memory area
* @b: the byte to fill *s with
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *_setmemory(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* free_f - frees a string of strings
* @ss: string of strings
*/
void free_f(char **ss)
{
char **a = ss;

if (!ss)
return;
while (*ss)
free(*ss++);
free(a);
}

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous malloc block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to block.
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
