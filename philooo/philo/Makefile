CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = src/main.c src/error_handling.c src/initilize.c 
NAME = philo
OBJ = $(SRCS:.c=.o)

# Default target to build the executable
all: $(NAME)

# Link the object files to create the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compile .c files into .o object files
$(OBJ): %.o: %.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ)

# Remove object files and the executable
fclean: clean
	rm -rf $(NAME)

# Rebuild everything (clean and then all)
re: fclean all

# Ensure these targets are always executed even if files exist with the same name
.PHONY: all clean fclean re
