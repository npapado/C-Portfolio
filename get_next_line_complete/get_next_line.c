
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

static int	extract_line(char **stash, char **line)
{
	size_t	i;
	char	*newline;
	char	*rest;

	if (!*stash)
	{
		*line = gnl_strdup("");
		return (0);
	}
	newline = gnl_strchr(*stash, '\n');
	if (newline)
	{
		i = (size_t)(newline - *stash);
		*line = gnl_substr(*stash, 0, i);
		rest = gnl_strdup(newline + 1);
		free(*stash);
		*stash = rest;
		return (1);
	}
	*line = *stash;
	*stash = NULL;
	return (0);
}

static int	read_to_stash(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	rd;

	while (!gnl_strchr(*stash, '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (-1);
		if (rd == 0)
			return (0);
		buffer[rd] = '\0';
		*stash = gnl_strjoin_free(*stash, buffer);
		if (!*stash)
			return (-1);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*stash;
	int			status;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	status = read_to_stash(fd, &stash);
	if (status == -1)
		return (-1);
	if (status == 0 && (!stash || *stash == '\0'))
	{
		*line = gnl_strdup("");
		free(stash);
		stash = NULL;
		return (0);
	}
	return (extract_line(&stash, line));
}
