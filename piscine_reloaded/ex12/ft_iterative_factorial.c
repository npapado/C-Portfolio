int ft_iterative_factorial(int nb)
{
    int result;

    if (nb < 0)
    {
        return 0;  // Return 0 for negative numbers
    }
    
    result = 1;  // Initialize result to 1 (since factorial of 0 is 1)
    
    while (nb > 1)
    {
        result *= nb;  // Multiply result by the current value of nb
        nb--;           // Decrement nb by 1
    }
    
    return result;
}
