
#include "get_next_line_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

static t_fdnode	*find_or_create(t_fdnode **head, int fd)
{
	t_fdnode	*cur;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	cur = (t_fdnode *)malloc(sizeof(t_fdnode));
	if (!cur)
		return (NULL);
	cur->fd = fd;
	cur->stash = NULL;
	cur->next = *head;
	*head = cur;
	return (cur);
}

static void	remove_node(t_fdnode **head, int fd)
{
	t_fdnode	*prev;
	t_fdnode	*cur;

	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->stash);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

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
	static t_fdnode	*head;
	t_fdnode		*node;
	int				status;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	node = find_or_create(&head, fd);
	if (!node)
		return (-1);
	status = read_to_stash(fd, &node->stash);
	if (status == -1)
		return (-1);
	if (status == 0 && (!node->stash || *node->stash == '\0'))
	{
		*line = gnl_strdup("");
		remove_node(&head, fd);
		return (0);
	}
	status = extract_line(&node->stash, line);
	if (status == 0 && (!node->stash || *node->stash == '\0'))
		remove_node(&head, fd);
	return (status);
}
