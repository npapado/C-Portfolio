
#include "fillit.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s) return 0;
    while (s[i]) i++;
    return i;
}

void   *ft_memset(void *b, int c, size_t n)
{
    size_t i = 0;
    unsigned char *p = (unsigned char*)b;
    while (i < n) p[i++] = (unsigned char)c;
    return b;
}

void    ft_putstr_fd(const char *s, int fd)
{
    if (!s) return;
    write(fd, s, ft_strlen(s));
}

void    ft_putendl_fd(const char *s, int fd)
{
    if (!s) return;
    write(fd, s, ft_strlen(s));
    write(fd, "\n", 1);
}

void    ft_putboard(char board[MAX_BOARD][MAX_BOARD], int size)
{
    int y, x;
    char nl = '\n';
    for (y = 0; y < size; ++y)
    {
        for (x = 0; x < size; ++x)
        {
            write(1, &board[y][x], 1);
        }
        write(1, &nl, 1);
    }
}
