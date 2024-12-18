#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int size;
	char *dup;

	size = 0;
	while (*src++)
	{
		size++;
	}

	dup = malloc(sizeof(char)* (size+1));
	
	if (!dup)  // Always check if malloc succeeded
    {
        return (NULL);
    }

	while (size>=0)
	{
		dup[size] = *--src;
		size--;
	}

	return (dup);
}
