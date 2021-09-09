#include "include/list.h"

_list* init_list(size_t size)
{
	_list* list = calloc(1, sizeof(struct LIST_STRUCT));
	list->items = 0;
	list->item_size = size;
	list->size = 0;

	return list;
};

void list_push(_list* list, void* item)
{
	list->size += 1;
	if (!list->items)
		list->items = calloc(1, list->item_size);
	else
		list->items = realloc(list->items, (list->size * list->item_size));

	list->items[list->size - 1] = item;
};

