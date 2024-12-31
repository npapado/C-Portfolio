# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = objs

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Library name
LIB_NAME = libft.a

# Targets
all: $(LIB_NAME)

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to create the static library
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean object files and the library
fclean: clean
	rm -f $(LIB_NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
