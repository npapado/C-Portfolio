#include <stdlib.h>

char    *ft_strdup(char *src)
{
    char    *dup;
    int     len;
    int     i;

    len = 0;
    while (src[len])  // Calculate the length of the source string
    {
        len++;
    }

    dup = (char *)malloc(sizeof(char) * (len + 1));  // Allocate memory for the duplicate string

    if (dup == NULL)  // Check if malloc failed
    {
        return (NULL);
    }

    i = 0;
    while (src[i])  // Copy the string to the new memory
    {
        dup[i] = src[i];
        i++;
    }

    dup[i] = '\0';  // Null-terminate the new string

    return (dup);  // Return the pointer to the new string
}
