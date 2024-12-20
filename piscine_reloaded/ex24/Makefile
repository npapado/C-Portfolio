# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = srcs
INC_DIR = includes

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o)

# Library name
LIB_NAME = libft.a

# Targets
all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS) -I$(INC_DIR)
	ar rcs $(LIB_NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all
