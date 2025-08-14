
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);

/* utils */
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin_free(char *s1, const char *s2);

typedef struct s_fdnode
{
	int					fd;
	char				*stash;
	struct s_fdnode		*next;
}	t_fdnode;

#endif
