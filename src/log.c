#include "malloc.h"

void
print_zone(t_zone *zone)
{
	t_chunk *chnk = (void *)zone + sizeof(t_zone);
	void	*tmp;

	if (zone->type == BIG)
	{
		tmp = (void *)zone + sizeof(t_zone);
		ft_printf("%p - %p : %zu bytes\n", tmp, tmp + zone->t_size, zone->t_size);
		return;
	}
	while (chnk)
	{
		if (chnk->used)
		{
			tmp = (void *)chnk + sizeof(t_chunk);
			ft_printf("%p - %p : %zu bytes\n", tmp, tmp + chnk->size, chnk->size);
		}
		chnk = chnk->next;
	}
}

void
show_alloc_mem()
{
	t_zone *zone = anchor;

	ft_printf("\n\n");
	if (!zone)
	{
		ft_printf("Total: 0 bytes\n");
		ft_printf("finished\n");
		return;
	}
	while (zone)
	{
		if (zone->type == TINY)
			ft_printf("TINY : %p, length: %zu\n", zone, zone->t_size);
		else if (zone->type == MEDIUM)
			ft_printf("SMALL: %p, length: %zu\n", zone, zone->t_size);
		else if (zone->type == BIG)
			ft_printf("BIG: %p, length: %zu\n", zone, zone->t_size);
		if (zone->blk_cnt || zone->type == BIG)
			print_zone(zone);
		zone = zone->next;
	}
}
