#include "malloc.h"

void	print_zone(t_zone *zone)
{
	t_chunk *chnk = (void*)zone + sizeof(t_zone);
	void	*tmp;

	if (zone->type == BIG)
	{
		tmp = (void*)zone + sizeof(t_zone);
		fprintf(stderr, "%p - %p : %zu bytes\n", tmp, tmp + zone->t_size, zone->t_size);
	}
	while (chnk)
	{
		if (chnk->used)
		{
			tmp = (void*)chnk + sizeof(t_chunk);
			fprintf(stderr, "%p - %p : %zu bytes\n", tmp, tmp + chnk->size, chnk->size);
		}
		chnk = chnk->next;
	}
}

void	show_alloc_mem()
{
	t_zone *zone = anchor;
	
	if (!zone)
	{
		fprintf(stderr, "Total: 0 bytes\n");
		return ;
	}
	while (zone)
	{
		if (zone->type == TINY)
			fprintf(stderr, "TINY : %p\n", zone);
		else if (zone->type == MEDIUM)
			fprintf(stderr, "SMALL: %p\n", zone);
		else if (zone->type == BIG)
			fprintf(stderr, "BIG: %p\n", zone);
		if (zone->blk_cnt || zone->type == BIG)
			print_zone(zone);
		zone = zone->next;
	}
}
