
#include "fillit.h"

void    board_clear(char board[MAX_BOARD][MAX_BOARD], int size)
{
    int y, x;
    for (y = 0; y < size; ++y)
        for (x = 0; x < size; ++x)
            board[y][x] = '.';
}

int     can_place(const t_piece *p, char board[MAX_BOARD][MAX_BOARD], int size, int x, int y)
{
    int i;
    (void)size;
    for (i = 0; i < 4; ++i)
    {
        int xx = x + p->b[i].x;
        int yy = y + p->b[i].y;
        if (xx < 0 || yy < 0 || xx >= size || yy >= size)
            return 0;
        if (board[yy][xx] != '.')
            return 0;
    }
    return 1;
}

void    place_piece(const t_piece *p, char board[MAX_BOARD][MAX_BOARD], int x, int y, char c)
{
    int i;
    for (i = 0; i < 4; ++i)
    {
        int xx = x + p->b[i].x;
        int yy = y + p->b[i].y;
        board[yy][xx] = c;
    }
}
