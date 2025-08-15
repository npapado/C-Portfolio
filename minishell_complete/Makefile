NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
SRCS = minishell.c parser.c utils.c executor.c builtins.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
