
NAME    = ft_select
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
LIBS    = -ltermcap

SRC     = main.c term.c ui.c signals.c input.c utils.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
