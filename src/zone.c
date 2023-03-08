#include "malloc.h"

t_zone *
get_free(short int type, size_t size)
{
	t_zone *tmp = anchor;

	while (tmp)
	{
		if (tmp->fr_size >= size + sizeof(t_chunk) && tmp->type == type)
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

	new = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (new == MAP_FAILED)
	{
		return (0);
	}
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
