#include "malloc.h"

t_zone	*create_zone(size_t	size)
{
	t_zone *new;
	size_t len;
	len = size + sizeof(t_zone);

	new = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (anchor == MAP_FAILED)
	{
		perror("mmap error\n");
		return (0);
	}
	new->t_size = len;
	return new;
}
