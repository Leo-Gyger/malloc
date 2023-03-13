NAME =	malloc.so
DB =	lldb

CC = gcc
CFLAGS =	-Wall -Wextra -Werror -fPIC -g
OFLAGS = 	-shared
SRCD =	src
SRCS = src/malloc.c
SRCS += src/zone.c
SRCS += src/chunk.c
SRCS += src/free.c
SRCS += src/realloc.c
SRCS += src/log.c

INCD = header
INCS = header/malloc.h

OBJD =	obj
OBJS =	$(patsubst $(SRCD)/%.c, $(OBJD)/%.o, $(SRCS))

all : $(NAME)
$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(OFLAGS) -o $(NAME)

$(OBJD)/%.o: $(SRCD)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(<) $(CFLAGS) -o $(@) -I $(INCD)

db: $(NAME)
	$(DB) $(NAME)

clean:
	rm -rf $(OBJD)
fclean: clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean db fclean re
