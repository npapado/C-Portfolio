int ft_sqrt(int nb)
{
    int i;

    if (nb < 0)
    {
        return 0;  // Negative numbers don't have a real square root
    }

    i = 0;
    while (i * i <= nb)
    {
        if (i * i == nb)
        {
            return i;  // If we find an integer whose square is nb, return it
        }
        i++;
    }

    return 0;  // If no such integer exists, return 0
}
