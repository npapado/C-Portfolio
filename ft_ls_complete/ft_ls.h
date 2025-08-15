#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <errno.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_opts {
	int l;
	int R;
	int a;
	int r;
	int t;
} t_opts;

typedef struct s_entry {
	char		*name;
	char		*path;
	struct stat	st;
	int			is_dir;
	int			is_link;
} t_entry;

typedef struct s_vec {
	t_entry *data;
	size_t   len;
	size_t   cap;
} t_vec;

/* parse.c */
int  parse_args(int argc, char **argv, t_opts *o, char ***paths_out, int *npaths);

/* vec.c */
void vec_init(t_vec *v);
void vec_push(t_vec *v, t_entry e);
void vec_free(t_vec *v);

/* collect.c */
int  collect_dir(const char *path, const t_opts *o, t_vec *out);
int  stat_path(const char *path, t_entry *e);

/* sort.c */
void sort_entries(t_vec *v, const t_opts *o);

/* print.c */
void print_entries(const char *header, const t_vec *v, const t_opts *o, int print_header);
void print_error_path(const char *path);

/* recurse.c */
int  ls_path(const char *path, const t_opts *o, int print_header);

#endif
