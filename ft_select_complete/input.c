
#include "ft_select.h"
#include <string.h>

int read_key(int fd, char *buf, size_t n)
{
    ssize_t r = read(fd, buf, n);
    if (r <= 0) return 0;
    return (int)r;
}

static void move_up(t_state *st)
{
    if (st->cur > 0) st->cur--;
    if (st->cur < st->top) st->top = st->cur;
}

static void move_down(t_state *st)
{
    if (st->cur < st->count - 1) st->cur++;
    int max_lines = st->rows - 1;
    if (st->cur >= st->top + max_lines) st->top = st->cur - (max_lines - 1);
}

static void delete_current(t_state *st)
{
    int i;
    if (st->count == 0) return;
    /* remove current */
    for (i = st->cur; i < st->count - 1; ++i)
        st->items[i] = st->items[i+1];
    st->count--;
    if (st->cur >= st->count) st->cur = st->count - 1;
    if (st->cur < 0) st->cur = 0;
    if (st->top > st->cur) st->top = st->cur;
}

int handle_key(t_state *st)
{
    char buf[8] = {0};
    int n = read_key(0, buf, sizeof(buf));
    if (n == 0) return 0;

    /* Arrow keys (ESC [ A/B) */
    if (buf[0] == 27 && n >= 3 && buf[1] == '[')
    {
        if (buf[2] == 'A') move_up(st);
        else if (buf[2] == 'B') move_down(st);
        return 1;
    }
    /* Space: toggle */
    if (buf[0] == ' ')
    {
        if (st->count > 0)
            st->items[st->cur].selected = !st->items[st->cur].selected;
        move_down(st);
        return 1;
    }
    /* Enter */
    if (buf[0] == '\n' || buf[0] == '\r')
    {
        int first = 1;
        term_restore(st);
        for (int i = 0; i < st->count; ++i)
            if (st->items[i].selected)
            {
                if (!first) write(1, " ", 1);
                first = 0;
                write(1, st->items[i].text, strlen(st->items[i].text));
            }
        write(1, "\n", 1);
        return 2; /* done */
    }
    /* Esc: quit */
    if (buf[0] == 27 && n == 1)
    {
        term_restore(st);
        return 2;
    }
    /* Backspace or Delete */
    if (buf[0] == 127 || buf[0] == 8 || (buf[0] == 27 && n >= 4 && buf[1]=='[' && buf[2]=='3' && buf[3]=='~'))
    {
        delete_current(st);
        return 1;
    }
    return 1;
}
