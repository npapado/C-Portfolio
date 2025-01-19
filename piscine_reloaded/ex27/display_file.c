#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void display_error(char *message)
{
    while (*message)
    {
        write(2, message, 1);
        message++;
    }
}

int main(int argc, char **argv)
{
    int fd;
    int bytes_read;
    char buffer[BUFFER_SIZE];

    if (argc < 2)
    {
        display_error("File name missing.\n");
        return (1);
    }
    if (argc > 2)
    {
        display_error("Too many arguments.\n");
        return (1);
    }

    fd = open(argv[1], O_RDONLY);  // This will always succeed based on the assumption
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(1, buffer, bytes_read);
    }

    close(fd);
    return (0);
}