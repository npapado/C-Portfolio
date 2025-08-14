
#include "fillit.h"

static void usage(void)
{
    ft_putendl_fd("usage: fillit input_file", 1);
}

int main(int argc, char **argv)
{
    t_input in;
    char board[MAX_BOARD][MAX_BOARD];
    int size;

    if (argc != 2)
    {
        usage();
        return 0;
    }
    if (!parse_file(argv[1], &in))
    {
        ft_putendl_fd("error", 1);
        return 0;
    }
    if (!solve(&in, &size, board))
    {
        ft_putendl_fd("error", 1);
        return 0;
    }
    ft_putboard(board, size);
    return 0;
}
