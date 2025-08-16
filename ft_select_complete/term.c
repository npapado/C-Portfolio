
#include "ft_select.h"
#include <fcntl.h>
#include <string.h>

int putc_tc(int c) { return write(1, &c, 1); }

static int load_caps(t_caps *c)
{
    c->cl = tgetstr("cl", 0);
    c->cm = tgetstr("cm", 0);
    c->us = tgetstr("us", 0);
    c->ue = tgetstr("ue", 0);
    c->mr = tgetstr("mr", 0);
    c->me = tgetstr("me", 0);
    c->vi = tgetstr("vi", 0);
    c->ve = tgetstr("ve", 0);
    return (c->cl && c->cm && c->us && c->ue && c->mr && c->me);
}

int term_init(t_state *st)
{
    char *term;
    struct termios raw;
    struct winsize ws;

    st->tty_fd = 1; /* assume stdout is tty */
    if (!isatty(st->tty_fd))
        return -1;

    term = getenv("TERM");
    if (!term || tgetent(0, term) <= 0)
        return -1;
    if (!load_caps(&st->caps))
        return -1;

    if (tcgetattr(st->tty_fd, &st->orig) == -1)
        return -1;

    raw = st->orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(st->tty_fd, TCSANOW, &raw) == -1)
        return -1;

    if (ioctl(st->tty_fd, TIOCGWINSZ, &ws) == -1) { st->rows = 24; st->cols = 80; }
    else { st->rows = ws.ws_row; st->cols = ws.ws_col; }

    tputs(st->caps.vi, 1, putc_tc); /* hide cursor */
    return 0;
}

void term_restore(t_state *st)
{
    tcsetattr(st->tty_fd, TCSANOW, &st->orig);
    tputs(st->caps.ve, 1, putc_tc); /* show cursor */
    tputs(st->caps.me, 1, putc_tc); /* reset modes */
    tputs(st->caps.cl, 1, putc_tc); /* clear */
}
