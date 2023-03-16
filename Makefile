DB =	lldb
ifeq ($(HOSTTYPE),)
	HOSTTYPE := libft_malloc_$(shell uname -m)_$(shell uname -s).so
endif
LIBFT = ./libft/libft.a
MLIBFT			=		$(MAKE) -C libft
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

all : $(HOSTTYPE)
$(HOSTTYPE):	$(OBJS)
	@$(MLIBFT) all
	@$(CC) $(OBJS) ${LIBFT} $(OFLAGS) -o $(HOSTTYPE)

$(OBJD)/%.o: $(SRCD)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(<) $(CFLAGS) -o $(@) -I $(INCD)

db: $(HOSTTYPE)
	$(DB) $(HOSTTYPE)

clean:
	@$(MLIBFT) clean
	rm -rf $(OBJD)
fclean: clean
	@$(MLIBFT) fclean
	@rm -rf $(HOSTTYPE)

re:	fclean all

.PHONY: all clean db fclean re
