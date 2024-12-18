int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)  // Continue as long as both strings are non-empty
    {
        if (*s1 != *s2)  // If characters differ, return their difference
        {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;  // Move to the next character in s1
        s2++;  // Move to the next character in s2
    }

    // If both strings are of different lengths, return the difference
    return (unsigned char)*s1 - (unsigned char)*s2;
}
