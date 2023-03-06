NAME =	malloc
CC =	gcc
DB =	lldb

CFLAGS =	-Wall -Wextra -Werror
OFLAGS = 	-fsanitize=address

SRCD =	src
SRCS = src/malloc.c
OBJD =	obj
OBJS =	$(patsubst $(SRCD)/%.c, $(OBJD)/%.o, $(SRCS))

all : $(NAME)
$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(OFLAGS) -o $(NAME)

$(OBJD)/%.o: $(SRCD)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(<) $(CFLAGS) -o $(@)

db: $(NAME)
	$(DB) $(NAME)

clean:
	rm -rf $(OBJD)
fclean: clean
	@ rm -rf %(NAME)

re:	fclean all

.PHONY: all clean db fclean re
