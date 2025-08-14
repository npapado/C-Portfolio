
#include "fillit.h"

static int  is_valid_char(char c) { return (c == '.' || c == '#'); }

static int  count_adj(char grid[4][4], int y, int x)
{
    int c = 0;
    if (y > 0 && grid[y-1][x] == '#') c++;
    if (y < 3 && grid[y+1][x] == '#') c++;
    if (x > 0 && grid[y][x-1] == '#') c++;
    if (x < 3 && grid[y][x+1] == '#') c++;
    return c;
}

static void normalize_piece(char grid[4][4], t_piece *p, char id)
{
    int minx = 4, miny = 4, maxx = -1, maxy = -1;
    int y, x, k = 0;

    for (y = 0; y < 4; ++y)
        for (x = 0; x < 4; ++x)
            if (grid[y][x] == '#')
            {
                if (x < minx) minx = x;
                if (y < miny) miny = y;
                if (x > maxx) maxx = x;
                if (y > maxy) maxy = y;
            }
    p->w = (maxx - minx + 1);
    p->h = (maxy - miny + 1);
    for (y = 0; y < 4; ++y)
        for (x = 0; x < 4; ++x)
            if (grid[y][x] == '#')
            {
                p->b[k].x = x - minx;
                p->b[k].y = y - miny;
                k++;
            }
    p->id = id;
}

static int  read_piece(int fd, t_piece *p, char id, int *last_read_was_sep)
{
    char buf[21];
    ssize_t r;
    int i, y, x;
    char grid[4][4];
    int hashes = 0;
    int links = 0;

    r = read(fd, buf, 20);
    if (r == 0) return 0; /* EOF */
    if (r != 20) return -1;
    /* Validate structure: 4 lines of 4 chars + newline each */
    for (y = 0, i = 0; y < 4; ++y)
    {
        for (x = 0; x < 4; ++x, ++i)
        {
            if (!is_valid_char(buf[i])) return -1;
            grid[y][x] = buf[i];
            if (buf[i] == '#') hashes++;
        }
        if (buf[i] != '\n') return -1;
        ++i;
    }
    if (hashes != 4) return -1;
    /* Count adjacency to ensure connectivity (sum 6 or 8) */
    for (y = 0; y < 4; ++y)
        for (x = 0; x < 4; ++x)
            if (grid[y][x] == '#')
                links += count_adj(grid, y, x);
    if (!(links == 6 || links == 8)) return -1;

    normalize_piece(grid, p, id);

    /* Read optional separator newline (between tetriminos) */
    r = read(fd, buf, 1);
    if (r == 1)
    {
        if (buf[0] != '\n') return -1;
        *last_read_was_sep = 1;
    }
    else
        *last_read_was_sep = 0;
    return 1;
}

int     parse_file(const char *path, t_input *in)
{
    int fd = -1;
    int ret, sep = 0;
    int count = 0;

    fd = open(path, O_RDONLY);
    if (fd < 0) return 0;
    while (count < MAX_TETRI)
    {
        t_piece p;
        ret = read_piece(fd, &p, 'A' + count, &sep);
        if (ret == 0) break;
        if (ret < 0) { close(fd); return 0; }
        in->pieces[count++] = p;
        if (!sep) break;
    }
    /* No trailing extra content allowed */
    {
        char tmp[1];
        if (read(fd, tmp, 1) > 0) { close(fd); return 0; }
    }
    close(fd);
    if (count == 0) return 0;
    in->count = count;
    return 1;
}
