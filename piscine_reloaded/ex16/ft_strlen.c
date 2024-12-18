int ft_strlen(char *str)
{
    int length = 0;

    while (*str)  // Loop until we encounter the null terminator
    {
        length++;  // Increment the length for each character
        str++;     // Move the pointer to the next character
    }

    return length;  // Return the length of the string
}
