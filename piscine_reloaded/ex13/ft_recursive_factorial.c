int ft_recursive_factorial(int nb)
{
    if (nb < 0)
    {
        return 0;  // Return 0 for negative numbers
    }
    if (nb == 0 || nb == 1)
    {
        return 1;  // Base case: 0! = 1 and 1! = 1
    }
    return nb * ft_recursive_factorial(nb - 1);  // Recursive case
}
