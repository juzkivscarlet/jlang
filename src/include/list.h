#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct LIST_STRUCT
{
	void**	items;
	size_t	size, item_size;
} _list;

_list*	init_list(size_t size);
void	list_push(_list* list, void* item);

#endif

