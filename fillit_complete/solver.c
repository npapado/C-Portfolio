
#include "fillit.h"

static int  backtrack(const t_input *in, int idx, int size, char board[MAX_BOARD][MAX_BOARD])
{
    int y, x;
    const t_piece *p;
    if (idx == in->count)
        return 1;
    p = &in->pieces[idx];
    for (y = 0; y + p->h <= size; ++y)
    {
        for (x = 0; x + p->w <= size; ++x)
        {
            if (can_place(p, board, size, x, y))
            {
                place_piece(p, board, x, y, p->id);
                if (backtrack(in, idx + 1, size, board))
                    return 1;
                place_piece(p, board, x, y, '.');
            }
        }
    }
    return 0;
}

static int  min_side(int nblocks)
{
    int s = 1;
    while (s * s < nblocks) s++;
    if (s > MAX_BOARD) s = MAX_BOARD;
    return s;
}

int     solve(const t_input *in, int *out_size, char out[MAX_BOARD][MAX_BOARD])
{
    int size = min_side(in->count * 4);
    board_clear(out, MAX_BOARD);
    while (size <= MAX_BOARD)
    {
        board_clear(out, size);
        if (backtrack(in, 0, size, out))
        {
            *out_size = size;
            return 1;
        }
        size++;
    }
    return 0;
}
