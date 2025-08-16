
#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct s_item {
    char            *text;
    int             selected;
    int             alive;
}   t_item;

typedef struct s_caps {
    char *cl;  /* clear screen */
    char *cm;  /* cursor move */
    char *us;  /* underline start */
    char *ue;  /* underline end */
    char *mr;  /* reverse on */
    char *me;  /* modes end */
    char *vi;  /* cursor invisible */
    char *ve;  /* cursor visible */
}   t_caps;

typedef struct s_state {
    struct termios   orig;
    int              tty_fd;
    int              rows;
    int              cols;
    int              count;
    int              cur;     /* index of current (cursor) */
    int              top;     /* first visible index (for scrolling) */
    t_item          *items;
    t_caps           caps;
}   t_state;

/* term.c */
int   term_init(t_state *st);
void  term_restore(t_state *st);
int   putc_tc(int c);

/* ui.c */
void  ui_refresh(t_state *st);
void  ui_resize(t_state *st);

/* signals.c */
void  setup_signals(t_state *st);

/* input.c */
int   read_key(int fd, char *buf, size_t n);
int   handle_key(t_state *st);

/* utils.c */
void *xmalloc(size_t n);
char *xstrdup(const char *s);

#endif
