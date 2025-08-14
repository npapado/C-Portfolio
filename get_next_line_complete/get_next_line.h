
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);

/* utils (no libft allowed) */
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin_free(char *s1, const char *s2);

#endif
