#include "malloc.h"

int	malloc_limit;

t_zone *
get_free(short int type, size_t size)
{
	t_zone *tmp = anchor;

	while (tmp)
	{
		if (tmp->fr_size >= size + sizeof(t_chunk) && tmp->type == type && tmp->fr_size != 0)
			return tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

t_zone *
create_zone(size_t size)
{
	t_zone *new, *last;
	size_t len;
	
	len = size + sizeof(t_zone);
	malloc_limit++;	
	new = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
		return (0);
	if (getenv("MallocPreScribble"))
		memset((void*)new + sizeof(t_zone), 0xAA, size);
	new->t_size = len;
	last = get_last();
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->fr_size = size;
	return new;
}
