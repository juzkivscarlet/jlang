#include <stdio.h>

#include "include/jlang.h"
#include "include/macros.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("please specify input file...\n");
		return 1;
	}

	_compilefile(argv[1]);

	return 0;
};

