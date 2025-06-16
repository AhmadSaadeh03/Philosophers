
CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a 

SRCS = ft_printf.c ft_lnum.c check.c
LIB = libft/
OBJS = $(SRCS:.c=.o)
LIBA = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB)
	@cp $(LIB)$(LIBA) .
	@mv $(LIBA) $(NAME)
	ar rcs $(NAME) $(OBJS)
clean:
	rm -f $(OBJS)
	@make -C $(LIB) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIB) fclean
re: fclean all
.PHONY: all fclean clean re
