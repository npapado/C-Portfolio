
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -D BUFFER_SIZE=32
RM		= rm -f

NAME	= gnl_test

SRC		= get_next_line.c get_next_line_utils.c
BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c

all:
	$(CC) $(CFLAGS) $(SRC) main.c -o $(NAME)

bonus:
	$(CC) $(CFLAGS) $(BONUS) main.c -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: clean all

.PHONY: all bonus clean fclean re
