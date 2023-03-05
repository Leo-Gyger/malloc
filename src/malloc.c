#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

intptr_t *zone = 0;

intptr_t *
get_last(void)
{
	intptr_t *tmp = zone;
	while (tmp)
	{
		if (tmp[1] == 0)
			return (tmp);
		tmp = (intptr_t *)tmp[1];
	}
	return (NULL);
}

void *
ft_malloc(size_t size)
{
	intptr_t *n_chunk, *last;
	intptr_t  len = size + (sizeof(intptr_t) * 3);

	if (!zone)
	{
		zone = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
		if (zone == MAP_FAILED)
		{
			fprintf(stderr, "mmap error\n");
			return (0);
		}
		zone[0] = len;
		zone[1] = 0;
		zone[2] = 0;
		return zone + 3;
	}
	else
	{
		last = get_last();
		n_chunk = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (n_chunk == MAP_FAILED)
		{
			fprintf(stderr, "mmap error\n");
			return (0);
		}
		n_chunk[0] = len;
		last[1] = (intptr_t)n_chunk;
		n_chunk[1] = 0;
		n_chunk[2] = (intptr_t)last;
		return n_chunk + 3;
	}
}

void
ft_free(void *ptr)
{
	intptr_t  tmp;
	intptr_t *prev, *next, *plen;

	if (!ptr)
	{
		perror("Trying to free void");
		return;
	}
	plen = ptr - (sizeof(intptr_t) * 3);
	if (plen == zone)
	{
		tmp = plen[1];
		if (munmap(plen, *plen))
		{
			perror((strerror(errno)));
			zone = 0;
		}
		zone = (intptr_t *)tmp;
	}
	else
	{
		prev = (intptr_t *)plen[2];
		prev[1] = plen[1];
		next = (intptr_t *)prev[1];
		if (next)
			next[2] = (intptr_t)prev;
		if (munmap(plen, *plen))
		{
			perror(strerror(errno));
			return;
		}
	}
}

int
main()
{
	char *str = ft_malloc(7);
	strcpy(str, "Hello ");
	str[6] = 0;
	char *str2 = ft_malloc(7);
	strcpy(str2, "World\n");
	str2[6] = 0;
	printf("%s%s", str, str2);
	ft_free(str);
	ft_free(str2);
	return 0;
}
