#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_swap(char **a, char **b)
{
    char    *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int    main(int argc, char *argv[])
{
    int    i;
    int    j;

    i = 1;
    while (i < argc)
    {
        j = i + 1;
        while (j < argc)
        {
            if (argv[i][0] > argv[j][0])
            {
                ft_swap(&argv[i], &argv[j]);
            }
            j++;
        }
        i++;
    }

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            ft_putchar(argv[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }

    return (0);
}
