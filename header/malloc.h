#ifndef MALLOC_H
#define MALLOC_H
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#define TINY_ZONE_SIZE ((128 + 32) * 100)
#define TINY 1
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

t_zone	*create_zone(size_t);
t_zone	*get_free(short int, size_t);
t_zone	*get_last();
t_chunk *crt_new(size_t, t_zone *);
void	 ft_free(void *);
#endif
