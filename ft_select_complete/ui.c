
#include "ft_select.h"
#include <string.h>

static void move_cursor(t_state *st, int x, int y)
{
    char *cm = tgoto(st->caps.cm, x, y);
    tputs(cm, 1, putc_tc);
}

void ui_resize(t_state *st)
{
    struct winsize ws;
    if (ioctl(st->tty_fd, TIOCGWINSZ, &ws) == -1) return;
    st->rows = ws.ws_row;
    st->cols = ws.ws_col;
    if (st->cur < st->top) st->top = st->cur;
    if (st->cur >= st->top + st->rows - 1) st->top = st->cur - (st->rows - 2);
    if (st->top < 0) st->top = 0;
    if (st->top > st->count - 1) st->top = st->count - 1;
}

void ui_refresh(t_state *st)
{
    int max_lines = st->rows - 1; /* keep last line for instructions/status */
    int idx = st->top;
    int y = 0;

    if (max_lines < 1) return;

    tputs(st->caps.cl, 1, putc_tc);
    move_cursor(st, 0, 0);

    for (y = 0; y < max_lines && idx < st->count; ++y, ++idx)
    {
        if (!st->items[idx].alive) continue;

        if (idx == st->cur && st->items[idx].selected)
            { tputs(st->caps.us,1,putc_tc); tputs(st->caps.mr,1,putc_tc); }
        else if (idx == st->cur)
            { tputs(st->caps.us,1,putc_tc); }
        else if (st->items[idx].selected)
            { tputs(st->caps.mr,1,putc_tc); }

        write(1, st->items[idx].text, strlen(st->items[idx].text));

        tputs(st->caps.me, 1, putc_tc);
        tputs(st->caps.ue, 1, putc_tc);
        write(1, "\n", 1);
    }

    /* Status/help line */
    move_cursor(st, 0, st->rows-1);
    write(1, "Arrows: move  Space: select  Del/Backspace: remove  Enter: confirm  Esc: quit", 79);
    move_cursor(st, 0, (st->cur - st->top));
}
