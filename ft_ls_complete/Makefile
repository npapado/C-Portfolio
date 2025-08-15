
NAME    = ft_ls
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES = -I include
SRC     = src/main.c src/args.c src/vec.c src/path.c src/read.c src/sort.c src/print.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

%.o: %.c include/ft_ls.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
