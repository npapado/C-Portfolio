# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Default target
all: libft.a

# Create the static library
libft.a: srcs/*.c
	$(CC) $(CFLAGS) -Iincludes -c srcs/*.c
	ar rcs libft.a srcs/*.o

# Clean object files
clean:
	rm -f srcs/*.o

# Clean and remove library
fclean: clean
	rm -f libft.a

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
