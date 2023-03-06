#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../header/malloc.h"
t_zone 	*anchor = 0;

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
ft_malloc(size_t size)
{
	t_zone	*last, *n_zone;
	size_t	len;
	len = size + sizeof(t_zone);

	if (!anchor)
	{
		anchor = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
		if (anchor == MAP_FAILED)
		{
			fprintf(stderr, "mmap error\n");
			return (0);
		}
		anchor->next = 0;
		anchor->prev = 0;
		anchor->t_size = len;
		anchor->fr_size = 0;
		anchor->type = 3;
		return anchor + sizeof(t_zone);
	}
	else
	{
		last = get_last();
		n_zone = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if (n_zone == MAP_FAILED)
		{
			fprintf(stderr, "mmap error\n");
			return (0);
		}
		n_zone->t_size = len;
		n_zone->fr_size = 0;
		n_zone->type = 3;
		last->next = n_zone;
		n_zone->next = 0;
		n_zone->prev = last;
		return n_zone + sizeof(t_zone);
	}
}

void
ft_free(void *ptr)
{
	t_zone   *prev, *next, *plen;

	if (!ptr)
	{
		perror("Trying to free void");
		return;
	}
	plen = ptr - 2304;
	if (plen == anchor)
	{
		next = plen->next;
		if (munmap(plen, plen->t_size))
		{
			perror((strerror(errno)));
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
