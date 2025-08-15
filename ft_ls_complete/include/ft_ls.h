
#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_flags {
	int l;
	int R;
	int a;
	int r;
	int t;
}	t_flags;

typedef struct s_entry {
	char		*name;      /* basename */
	char		*path;      /* full path */
	struct stat	sb;         /* lstat */
	int			is_dir;
	int			is_link;
}	t_entry;

typedef struct s_vec {
	t_entry *v;
	size_t   size;
	size_t   cap;
}	t_vec;

/* args */
void	parse_flags(int ac, char **av, t_flags *flg, int *first_non_flag);

/* vec */
void	vec_init(t_vec *vec);
void	vec_push(t_vec *vec, t_entry e);
void	vec_free(t_vec *vec);

/* path */
char	*join_path(const char *a, const char *b);

/* read */
int		read_dir(const char *path, const t_flags *flg, t_vec *out);
int		stat_entry(const char *path, const char *name, t_entry *e);

/* sort */
int		cmp_entries(const void *aa, const void *bb, void *ctx);
void	sort_entries(t_vec *vec, const t_flags *flg);

/* print */
void	print_entries(t_vec *vec, const char *header, const t_flags *flg);
void	print_long(const t_entry *e, int widths[3]);
void	print_error_path(const char *prefix, const char *name);

#endif
