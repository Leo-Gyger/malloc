#ifndef MALLOC_H
# define MALLOC_H
// A zone is a range of address claimed directly from the virtual memory
typedef struct s_zone {
	struct s_zone *prev;
	struct s_zone *next;
	short int	type;
	size_t		t_size;
	size_t		fr_size;
	size_t		blk_cnt;
}	t_zone;

// A chunk is a part of a block
typedef struct s_chunk {
	struct s_chunk	*next;
	struct s_chunk	*prev;
	size_t		size;
	short int	used;
}	t_chunk;

#endif
