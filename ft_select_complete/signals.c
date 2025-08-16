
#include "ft_select.h"
#include <string.h>

static t_state *g_state;

static void on_winch(int sig)
{
    (void)sig;
    if (!g_state) return;
    ui_resize(g_state);
    ui_refresh(g_state);
}

static void on_int(int sig)
{
    (void)sig;
    if (!g_state) return;
    term_restore(g_state);
    _exit(130);
}

static void on_tstp(int sig)
{
    (void)sig;
    if (!g_state) return;
    term_restore(g_state);
    signal(SIGTSTP, SIG_DFL);
    kill(0, SIGTSTP);
}

static void on_cont(int sig)
{
    (void)sig;
    if (!g_state) return;
    term_init(g_state);
    ui_refresh(g_state);
}

void setup_signals(t_state *st)
{
    g_state = st;
    signal(SIGWINCH, on_winch);
    signal(SIGINT, on_int);
    signal(SIGTSTP, on_tstp);
    signal(SIGCONT, on_cont);
}
