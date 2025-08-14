
#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define MAX_TETRI 26
# define MAX_BOARD 16

typedef struct s_coord { int x; int y; } t_coord;

typedef struct s_piece {
	int     w;
	int     h;
	t_coord b[4];   /* block offsets inside bounding box (0..w-1,0..h-1) */
	char    id;     /* 'A'.. */
} t_piece;

typedef struct s_input {
	t_piece pieces[MAX_TETRI];
	int     count;
} t_input;

/* parse.c */
int     parse_file(const char *path, t_input *in);

/* solver.c */
int     solve(const t_input *in, int *out_size, char out[MAX_BOARD][MAX_BOARD]);

/* board.c */
void    board_clear(char board[MAX_BOARD][MAX_BOARD], int size);
int     can_place(const t_piece *p, char board[MAX_BOARD][MAX_BOARD], int size, int x, int y);
void    place_piece(const t_piece *p, char board[MAX_BOARD][MAX_BOARD], int x, int y, char c);

/* utils.c */
size_t  ft_strlen(const char *s);
void   *ft_memset(void *b, int c, size_t n);
void    ft_putstr_fd(const char *s, int fd);
void    ft_putendl_fd(const char *s, int fd);
void    ft_putboard(char board[MAX_BOARD][MAX_BOARD], int size);

#endif
