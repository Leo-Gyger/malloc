#include "malloc.h"

t_zone *anchor = 0;
t_zone *
get_last(void)
{
	t_zone *tmp = anchor;
	while (tmp)
	{
		if (tmp->next == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void *
tiny_allocation(size_t size)
{
	t_chunk *blk;
	t_zone	*tmp;

	if (!anchor)
	{
		anchor = create_zone(TINY_ZONE_SIZE);
		anchor->type = 1;
	}
	tmp = get_free(TINY, size);
	if (!tmp)
	{
		tmp = create_zone(TINY_ZONE_SIZE);
		tmp->type = TINY;
	}
	blk = crt_new(size, tmp);
	tmp->blk_cnt++;
	return (void *)blk + sizeof(t_chunk);
}
void *
medium_allocation(size_t size)
{
	t_chunk *blk;
	t_zone	*tmp;

	if (!anchor)
	{
		anchor = create_zone(MEDIUM_ZONE_SIZE);
		anchor->type = 2;
	}
	tmp = get_free(MEDIUM, size);
	if (!tmp)
	{
		tmp = create_zone(MEDIUM_ZONE_SIZE);
		tmp->type = MEDIUM;
	}
	blk = crt_new(size, tmp);
	tmp->blk_cnt++;
	return (void *)blk + sizeof(t_chunk);
}

void *
big_allocation(size_t size)
{
	t_zone *n_zone;

	if (!anchor)
	{
		anchor = create_zone(size);
		anchor->type = 3;
		return (void *)anchor + sizeof(t_zone);
	}
	else
	{
		n_zone = create_zone(size);
		n_zone->type = 3;
		return (void *)n_zone + sizeof(t_zone);
	}
}

void *
malloc(size_t size)
{
	//size = (size + 15) & ~15;
	if (size < TINY_ZONE_SIZE / 128)
		return tiny_allocation(size);
	else if (size < MEDIUM_ZONE_SIZE / 128)
		return medium_allocation(size);
	else
		return big_allocation(size);
	fprintf(stderr, "malloc error\nsize: %zu\n", size);
	return 0;
}
/*
void
test1(void)
{
	char *str = ft_malloc(7);
	char *t_str = malloc(7);
	strcpy(str, "Hello ");
	strcpy(t_str, "Hello ");
	t_str[6] = 0;
	str[6] = 0;
	char *str2 = ft_malloc(7);
	char *t_str2 = malloc(7);
	strcpy(str2, "World\n");
	strcpy(t_str2, "World\n");
	str2[6] = 0;
	t_str2[6] = 0;
	char *test = ft_malloc(129);
	printf("----ft_malloc----\n");
	printf("content: %s%s", str, str2);
	printf("addresses: %p %p\n", str, str2);
	printf("----malloc----\n");
	printf("content: %s%s", t_str, t_str2);
	printf("addresses: %p %p\n", t_str, t_str2);
	char	*medium = ft_malloc(300);
	char	*big = ft_malloc(2000);
	show_alloc_mem();
	ft_free(str);
	ft_free(medium);
	ft_free(big);
	ft_free(test);
	free(t_str);
	ft_free(str2);
	free(t_str2);
} */

/*int
main()
{
	test1();
	char *str = ft_malloc(7);
	char *test = ft_malloc(100);
	strcpy(str, "hello ");
	printf("address pre realloc: %p\n", str);
	str = ft_realloc(str, 88);
	strcpy(str + strlen(str), "World\n");
	printf("realloc content/address: %s %p\n", str, str);
	ft_free(str);
	ft_free(test);
	return 0;
} */
