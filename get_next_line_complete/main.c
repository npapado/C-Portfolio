
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd = 0;
	char *line = NULL;
	int ret;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("[%d] %s\n", ret, line);
		free(line);
	}
	printf("[%d] %s\n", ret, line ? line : "(null)");
	free(line);
	if (fd > 2) close(fd);
	return 0;
}
