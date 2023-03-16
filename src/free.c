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
	size_t	size = plen->t_size;

	if (plen == anchor)
	{
		next = plen->next;
		if (getenv("MallocScribble"))
			memset(plen, 0x55, size);
		if (munmap(plen, size))
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
		if (getenv("MallocScribble"))
			memset(plen, 0x55, size);
		if (munmap(plen, size))
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
	/*	if (chnk->prev && !chnk->prev->used)
		{
			prev = chnk->prev;
			prev->size += chnk->size + sizeof(t_chunk);
			prev->next = chnk->next;
		} */
	if (zone->blk_cnt == 0)
		free_zone(zone);
	else if (getenv("MallocScribble"))
		memset(chnk, 0x55, chnk->size);
	return;
}

void
free(void *ptr)
{
	t_chunk *chnk;

	// show_alloc_mem();

	if (!ptr)
		return;
	if (get_type(ptr) == 3)
	{
		free_zone(ptr - sizeof(t_zone));
		return;
	}
	if (get_type(ptr) == 4)
	{
		//		fprintf(stderr, "error free\n");
		return;
	}
	chnk = get_chunk(ptr);
	if (chnk)
		free_cnk(chnk);
}
