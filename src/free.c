#include "malloc.h"

t_chunk *
get_chunk(void *ptr)
{
	t_chunk *chnk;
	chnk = ptr - sizeof(t_chunk);
	return (chnk);
}
short int
get_type(void *ptr)
{
	t_zone *tmp = anchor;

	while (tmp)
	{
		if (ptr < (void *)tmp + tmp->t_size && ptr > (void *)tmp)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (4);
}
void
free_zone(t_zone *plen)
{
	t_zone *prev, *next;
	if (plen == anchor)
	{
		next = plen->next;
		if (munmap(plen, plen->t_size))
		{
			anchor = 0;
		}
		anchor = next;
	}
	else
	{
		prev = plen->prev;
		prev->next = plen->next;
		next = prev->next;
		if (next)
			next->prev = prev;
		if (munmap(plen, plen->t_size))
		{
			return;
		}
	}
}

void
free_cnk(t_chunk *chnk)
{
	t_chunk *prev;
	t_zone	*zone;
	chnk->used = 0;
	prev = chnk;
	while (prev->prev)
		prev = prev->prev;
	zone = (void *)prev - sizeof(t_zone);
	zone->fr_size += chnk->size;
	--zone->blk_cnt;
	if (chnk->prev && !chnk->prev->used)
	{
		prev = chnk->prev;
		prev->size += chnk->size + sizeof(t_chunk);
		prev->next = chnk->next;
	}
	if (zone->blk_cnt == 0)
		free_zone(zone);
	return;
}

void
free(void *ptr)
{
	t_chunk *chnk;

	if (get_type(ptr) == 3)
	{
		free_zone(ptr - sizeof(t_zone));
		return;
	}
	if (!ptr)
	{
		return;
	}
	chnk = get_chunk(ptr);
	if (chnk)
		free_cnk(chnk);
}
