#include "malloc.h"

t_zone	*get_zone(void	*ptr)
{
	t_zone	*ret = anchor;

	while (ret)
	{
		if (ptr < (void*)ret + ret->t_size && ptr > (void*)ret)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_chunk	*extend_mem(t_zone *zone, t_chunk *chnk, size_t size)
{
	t_chunk *tmp = chnk;
	size_t	mem = chnk->size;
	size_t	old_nbr = zone->blk_cnt;
	while (tmp->next && !tmp->next->used)
	{
		if (size > tmp->next->size)
		{
			size -= tmp->next->size + sizeof(t_chunk);
			chnk->size += tmp->next->size + sizeof(t_chunk);
			--zone->blk_cnt;
		}
		else
		{
			chnk->next = tmp->next->next;
			chnk->size += size;
			--zone->blk_cnt;
			return (chnk);
		}
		tmp = tmp->next;
	}
	if (!tmp->next)
	{
		chnk->size += size;
		return (chnk);
	}
	chnk->size = mem;
	zone->blk_cnt = old_nbr;
	return (0);
}

void	*realloc(void	*ptr, size_t size)
{
	t_zone	*zone;
	t_chunk	*chnk;
	void	*n_ptr;


	size = (size + 15) & ~15;
	if (!ptr)
		ptr = malloc(size);
	else
	{
		zone = get_zone(ptr);
		chnk = get_chunk(ptr);
		if (zone->fr_size >= size)
		{
			if (chnk->size <= size)
				return ((void*)chnk + sizeof(t_chunk));
			if (extend_mem(zone, chnk, size))
				return ((void*)chnk + sizeof(t_chunk));
		}
		else
		{
			n_ptr = malloc(size);
			if (!n_ptr)
				return (0);
			return (n_ptr);
		}
	}
	return (NULL);
}


