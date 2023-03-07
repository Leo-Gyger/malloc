#include "malloc.h"

t_chunk *
get_first(t_zone *zone)
{
	t_chunk *tmp;
	void	*mem = zone;
	if (zone->blk_cnt == 0)
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
	if (!first)
	{
		first = (void *)zone + sizeof(t_zone);
		first->size = size;
		first->used = 1;
		return ((void *)first);
	}
	while (first->next)
	{
		if (first->size >= size && !first->used)
		{
			first->used = 1;
			return (first);
		}
		first = first->next;
	}
	if (first->size >= size && !first->used)
	{
		first->used = 1;
		return (first);
	}
	new = (void *)first + first->size + sizeof(t_chunk);
	zone->fr_size -= (size + sizeof(t_chunk));
	new->prev = first;
	first->next = new;
	new->used = 1;
	new->size = size;
	return (new);
}
