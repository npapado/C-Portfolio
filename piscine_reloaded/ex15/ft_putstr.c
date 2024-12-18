void ft_putchar(char c);

void ft_putstr(char *str)
{
    while (*str)  // Continue looping until we reach the null terminator ('\0')
    {
        ft_putchar(*str);  // Output the current character
        str++;  // Move to the next character in the string
    }
}
