#include <stdlib.h>
#include <string.h>

#include "include/types.h"

int type_toint(const char* name)
{
	size_t len	= strlen(name);
	int t		= 0;
	for (unsigned int i = 0; i < len; i++)
		t += name[i];

	return t;
};

