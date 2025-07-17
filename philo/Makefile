CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
SRCS = src/main.c src/error_handling.c src/initilize.c src/routine.c src/helper.c src/monitor_death.c
NAME = philo
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ): %.o: %.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
