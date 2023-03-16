#include "malloc.h"

t_chunk *
get_first(t_zone *zone)
{
	t_chunk *tmp;
	void	*mem = zone;
	if (!zone || zone->blk_cnt == 0 || zone->type == BIG)
	{
		return (NULL);
	}
	mem += sizeof(t_zone);
	tmp = mem;
	return tmp;
}

t_chunk *
crt_new(size_t size, t_zone *zone)
{
	t_chunk *first, *new;
	first = get_first(zone);
	if (!first || (getenv("MallocScribble") && first != (void*)0x55))
	{
		first = (void *)zone + sizeof(t_zone);
		first->size = size;
		first->next = 0;
		first->prev = 0;
		first->used = 1;
		zone->fr_size -= (size + sizeof(t_chunk));
		return ((void *)first);
	}
	while (first->next ||(getenv("MallocScribble") && first->next != (void*)0x55))
	{
		if (first->size >= size && !first->used)
		{
			first->used = 1;
			zone->fr_size -= (size + sizeof(t_chunk));
		//	fprintf(stderr, "found new one\n");
			return (first);
		}
		first = first->next;
	}
	if (first->size >= size && !first->used)
	{
		first->used = 1;
		zone->fr_size -= (size + sizeof(t_chunk));
		return (first);
	}
	new = (void *)first + first->size + sizeof(t_chunk);
	zone->fr_size -= (size + sizeof(t_chunk));
	new->prev = first;
	new->next = 0;
	first->next = new;
	new->used = 1;
	new->size = size;
	return (new);
}
