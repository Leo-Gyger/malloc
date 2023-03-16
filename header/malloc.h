#ifndef MALLOC_H
#define MALLOC_H
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/ft_printf.h"
#define TINY_ZONE_SIZE ((size_t)(2 * getpagesize()))
#define MEDIUM_ZONE_SIZE ((size_t)(4 * getpagesize()))
#define TINY 1
#define MEDIUM 2
#define BIG 3
// A zone is a range of address claimed directly from the virtual memory
typedef struct s_zone
{
	struct s_zone *prev;
	struct s_zone *next;
	short int	   type;
	size_t		   t_size;
	size_t		   fr_size;
	size_t		   blk_cnt;
} t_zone;

// A chunk is a part of a block
typedef struct s_chunk
{
	struct s_chunk *next;
	struct s_chunk *prev;
	size_t			size;
	short int		used;
} t_chunk;

extern t_zone *anchor;
extern int malloc_limit;
t_zone	*create_zone(size_t);
t_zone	*get_free(short int, size_t);
t_zone	*get_last();
t_chunk *crt_new(size_t, t_zone *);
t_chunk	*get_chunk(void*);
void	free(void *);
void	*realloc(void *, size_t);
void	*reallocf(void *, size_t);
void	*malloc(size_t);
void	*calloc(size_t, size_t);
void	show_alloc_mem();
#endif
