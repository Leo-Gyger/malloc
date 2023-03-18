NAME = libft.a
CFLAGS = -Wall -Wextra -g -I. -c
CC = gcc
FILES = ft_hexitoa.c\
		ft_itoa.c\
		ft_printf.c\
		ft_shexitoa.c\
		ft_uitoa.c\
		ft_p.c\
		ft_putchar.c


OBJ = $(FILES:%.c=%.o)
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
$(OBJ): $(FILES)
	gcc $(CFLAGS) $(FILES)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: clean all

.PHONY: clean fclean all re
